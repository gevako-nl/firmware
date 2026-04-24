# Gevako RS6 | 6-Channel Smart Relay for Home Assistant

## Overview
The Gevako RS6 is an industrial-grade 6-channel Smart Relay board designed for Home Assistant via ESPHome. Powered by the ESP32-C6 RISC-V processor, it provides rock-solid local control using either **WiFi 6** or the **Thread** protocol. 

It features six fully independent relays, each capable of switching up to 16 A at 250 VAC / 30 VDC.

<a href="https://www.gevako.com/shop/" target="_blank">
<img alt="gevako-rs6-smart-relay-3d-front-left-thread-wifi" src="https://github.com/user-attachments/assets/7173222b-00c2-429f-a48f-1df1cb0600a4" width="200"/>
</a>

🔗 **Hardware Details & Store:**
* [Gevako RS6 - Smart Relay](https://www.gevako.com/shop/gevako-rs6-smart-relay-home-assistant/)

---

## ⚡ Technical Specifications

### ESP32-C6 GPIO Pinout

| GPIO Pin | Function                  |
| :---     | :---                      |
| `GPIO00` | Relay Output 1            |
| `GPIO01` | Relay Output 2            |
| `GPIO02` | Relay Output 3            |
| `GPIO03` | Relay Output 4            |
| `GPIO04` | Relay Output 5            |
| `GPIO05` | Relay Output 6            |
| `GPIO08` | Status LED (Green)        |
| `GPIO09` | BOOT Button               |
| `GPIO14` | Power source detection    |

### Electrical Schematic & Terminals

| Terminal | Label | Description                                       |
| :---     | :---  | :---                                              |
| 1        | L1    | Power source input 1. Max 250 VAC / 30 VDC 16 A.  |
| 2        | O1    | Switched output 1. Max 250 VAC / 30 VDC 16 A.     |
| 3        | L2    | Power source input 2. Max 250 VAC / 30 VDC 16 A.  |
| 4        | O2    | Switched output 2. Max 250 VAC / 30 VDC 16 A.     |
| 5        | L3    | Power source input 3. Max 250 VAC / 30 VDC 16 A.  |
| 6        | O3    | Switched output 3. Max 250 VAC / 30 VDC 16 A.     |
| 7        | L4    | Power source input 4. Max 250 VAC / 30 VDC 16 A.  |
| 8        | O4    | Switched output 4. Max 250 VAC / 30 VDC 16 A.     |
| 9        | L5    | Power source input 5. Max 250 VAC / 30 VDC 16 A.  |
| 10       | O5    | Switched output 5. Max 250 VAC / 30 VDC 16 A.     |
| 11       | L6    | Power source input 6. Max 250 VAC / 30 VDC 16 A.  |
| 12       | O6    | Switched output 6. Max 250 VAC / 30 VDC 16 A.     |
| 13       | L     | Board Power: Phase 230 VAC.                       |
| 14       | N     | Board Power: Null 230 VAC.                        |
| 22       | B     | BOOT / Reboot (2 s) / Factory reset (10 s)        |
| 23-24    | USB   | USB-C connector. Max 5 VDC (1 A) for provisioning.|

<img alt="Gevako RS6 PCB Layout and Schematic" width="600" src="https://github.com/user-attachments/assets/3187ef04-c485-4fcf-9b61-99d80f0bda09" />

---

## 🛠️ Installation & Wiring

### Wiring Example
<img alt="Gevako RS6 Wiring Example Home Assistant" width="600" src="https://github.com/user-attachments/assets/3e578544-4c16-45c5-b363-5d55fe7742ed" />

### Provisioning (WiFi & Thread)
The RS6 is fully compatible with ESPHome and can be provisioned using standard WiFi or integrated directly into a **Thread** network using USB TLV code provisioning.

1. **WiFi / Thread ESPHome Installer:** [gevako.com/esphome](https://www.gevako.com/esphome/)
2. **Thread Provisioning Tool:** [gevako.com/thread](https://www.gevako.com/thread/)
3. **Official ESPHome Web:** [web.esphome.io](https://web.esphome.io/)
