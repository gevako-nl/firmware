#pragma once

/**
 * GEVAKO Thread Provisioning
 * ──────────────────────────
 * Beschermd met 'inline' keywords om linker-fouten te voorkomen.
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cstdlib>

#include "nvs_flash.h"
#include "nvs.h"
#include "esp_openthread.h"
#include "openthread/dataset.h"
#include "openthread/ip6.h"
#include "openthread/thread.h"
#include "driver/usb_serial_jtag.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// ── Configuration ─────────────────────────────────────────────────────────────

#define PROV_TAG       "GEVAKO_PROV"
#define PROV_NVS_NS    "gevako_ot"
#define PROV_NVS_KEY   "tlv"

// ── Namespace ─────────────────────────────────────────────────────────────────

namespace thread_prov {

// 'inline' variabelen zorgen ervoor dat er maar één instantie bestaat in het hele programma
inline bool s_uart_ready  = false;
inline bool s_provisioned = false;   // true once TLV has been successfully applied
inline std::string s_rx_buf;

// ─────────────────────────────────────────────────────────────────────────────
// NVS helpers
// ─────────────────────────────────────────────────────────────────────────────

inline bool nvs_save(const std::string& hex) {
    nvs_handle_t h;
    if (nvs_open(PROV_NVS_NS, NVS_READWRITE, &h) != ESP_OK) {
        ESP_LOGE(PROV_TAG, "NVS open (write) failed");
        return false;
    }
    bool ok = (nvs_set_str(h, PROV_NVS_KEY, hex.c_str()) == ESP_OK);
    nvs_commit(h);
    nvs_close(h);
    if (ok) ESP_LOGI(PROV_TAG, "TLV saved to NVS (%u chars)", (unsigned)hex.size());
    else    ESP_LOGE(PROV_TAG, "NVS write failed");
    return ok;
}

inline std::string nvs_load() {
    nvs_handle_t h;
    if (nvs_open(PROV_NVS_NS, NVS_READONLY, &h) != ESP_OK)
        return "";   // namespace does not exist yet = not provisioned

    size_t sz = 0;
    if (nvs_get_str(h, PROV_NVS_KEY, nullptr, &sz) != ESP_OK || sz == 0) {
        nvs_close(h);
        return "";
    }
    std::vector<char> buf(sz);
    if (nvs_get_str(h, PROV_NVS_KEY, buf.data(), &sz) != ESP_OK) {
        nvs_close(h);
        return "";
    }
    nvs_close(h);
    return std::string(buf.data());
}

// ─────────────────────────────────────────────────────────────────────────────
// Apply OpenThread dataset
// ─────────────────────────────────────────────────────────────────────────────

inline bool apply_tlv(const std::string& hex) {
    if (hex.empty() || hex.size() % 2 != 0) {
        ESP_LOGE(PROV_TAG, "Invalid TLV (length=%u)", (unsigned)hex.size());
        return false;
    }

    otOperationalDatasetTlvs ds;
    ds.mLength = hex.size() / 2;

    if (ds.mLength > OT_OPERATIONAL_DATASET_MAX_LENGTH) {
        ESP_LOGE(PROV_TAG, "TLV too long (%u bytes)", (unsigned)ds.mLength);
        return false;
    }

    for (size_t i = 0; i < ds.mLength; i++) {
        char b[3] = { hex[i * 2], hex[i * 2 + 1], '\0' };
        ds.mTlvs[i] = (uint8_t)strtol(b, nullptr, 16);
    }

    otInstance* ot = esp_openthread_get_instance();
    if (!ot) {
        ESP_LOGE(PROV_TAG, "OpenThread instance is NULL");
        return false;
    }

    if (otDatasetSetActiveTlvs(ot, &ds) != OT_ERROR_NONE) {
        ESP_LOGE(PROV_TAG, "otDatasetSetActiveTlvs failed");
        return false;
    }

    // Start Thread if not already running
    if (!otIp6IsEnabled(ot))
        otIp6SetEnabled(ot, true);
    if (otThreadGetDeviceRole(ot) == OT_DEVICE_ROLE_DISABLED)
        otThreadSetEnabled(ot, true);

    s_provisioned = true;
    ESP_LOGI(PROV_TAG, "TLV applied (%u bytes) — Thread started", (unsigned)ds.mLength);
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// USB provisioning interface
// ─────────────────────────────────────────────────────────────────────────────

inline void usb_write(const char* msg) {
    usb_serial_jtag_write_bytes((const uint8_t*)msg, strlen(msg), 0);
}

inline void uart_start() {
    if (s_uart_ready) return;
    s_uart_ready = true;

    vTaskDelay(pdMS_TO_TICKS(200));

    usb_write(
        "\r\n╔══════════════════════════════════╗\r\n"
        "║  GEVAKO Thread Provisioning      ║\r\n"
        "╚══════════════════════════════════╝\r\n"
        "Send:   TLV:<hex_string><Enter>\r\n\r\n> "
    );

    ESP_LOGW(PROV_TAG, "Provisioning mode active — waiting for TLV via USB");
}

inline void uart_poll() {
    if (!s_uart_ready) return;

    uint8_t data[128];
    int n = usb_serial_jtag_read_bytes(data, sizeof(data), 0);
    if (n <= 0) return;

    for (int i = 0; i < n; i++) {
        char c = (char)data[i];
        // Echo back
        usb_serial_jtag_write_bytes((const uint8_t*)&c, 1, 0);

        if (c == '\r' || c == '\n') {
            usb_write("\r\n");

            while (!s_rx_buf.empty() && (unsigned char)s_rx_buf.back() < 32)
                s_rx_buf.pop_back();

            if (s_rx_buf.rfind("TLV:", 0) == 0) {
                std::string tlv = s_rx_buf.substr(4);
                std::transform(tlv.begin(), tlv.end(), tlv.begin(), ::tolower);

                if (nvs_save(tlv) && apply_tlv(tlv)) {
                    usb_write("\r\n OK: TLV saved! Rebooting in 2 seconds...\r\n");
                    vTaskDelay(pdMS_TO_TICKS(2000));
                    esp_restart();
                } else {
                    usb_write("\r\n ERROR: Invalid TLV — check the hex string.\r\n> ");
                }
            } else if (!s_rx_buf.empty()) {
                usb_write("   Usage: TLV:<hex_string>\r\n> ");
            } else {
                usb_write("> ");
            }

            s_rx_buf.clear();
        } else if (c >= 32 && c < 127) {
            s_rx_buf += c;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Entry points
// ─────────────────────────────────────────────────────────────────────────────

inline void on_boot() {
    std::string tlv = nvs_load();
    if (!tlv.empty()) {
        ESP_LOGI(PROV_TAG, "NVS TLV found (%u chars) — applying...", (unsigned)tlv.size());
        if (!apply_tlv(tlv)) {
            ESP_LOGE(PROV_TAG, "TLV apply failed — entering provisioning mode");
            uart_start();
        }
    } else {
        ESP_LOGW(PROV_TAG, "No TLV in NVS — entering provisioning mode");
        uart_start();
    }
}

inline bool is_provisioned() { return s_provisioned; }

} // namespace thread_prov