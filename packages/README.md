# Gevako Firmware Core Packages

## Overview
This directory contains the modular ESPHome configuration files (packages) that power the Gevako Smart Relay series (like the RS5 and RS6). 

These files act as the "engine" for the devices. By splitting the code into modular packages, we ensure that core logic, bug fixes, and feature additions are maintained in one central place and applied consistently across all Gevako hardware.

**Note for end-users:** You do not need to download or edit these files manually. Your personal ESPHome device configuration will automatically import these packages directly from GitHub.

## 📁 File Structure & Explanations

### 🧠 Core Logic & Connectivity
* **`rs-base.yaml`**
  The central brain of the firmware. This file contains the shared logic for the Status LED, the physical BOOT button behavior (short press to reboot, long press for factory reset), power source detection, and internal diagnostic sensors (such as uptime).
* **`rs-wifi.yaml`**
  The standard WiFi connectivity stack. It includes the configuration for the ESPHome Native API, Fallback Hotspot (AP mode), and OTA (Over-The-Air) update settings.
* **`rs-thread.yaml`**
  The OpenThread connectivity stack. This replaces WiFi for users running a Thread border router, enabling fast and robust IPv6 mesh communication.
* **`thread_provisioning.h`**
  A custom C++ header file. It allows the ESP32-C6 to securely receive Thread network credentials via a USB connection using TLV (Type-Length-Value) payloads.

### ⚙️ Hardware Definitions
* **`rs5-hardware.yaml`**
  Hardware-specific file for the Gevako RS5. Contains the exact GPIO pin mappings, relay configurations, and default substitutions for the 5-channel board.
* **`rs6-hardware.yaml`**
  Hardware-specific file for the Gevako RS6. Contains the exact GPIO pin mappings, relay configurations, and default substitutions for the 6-channel board.

## 🛠️ How It Works (Example)
Gevako firmware relies on ESPHome's `remote_package` feature. When a user installs a Gevako device, their local YAML file is incredibly lightweight and simply points to these files:

```yaml
packages:
  # 1. Load the specific hardware pinout
  hardware:
    url: [https://github.com/gevako-nl/firmware](https://github.com/gevako-nl/firmware)
    ref: main
    file: packages/rs6-hardware.yaml
    
  # 2. Load the central Gevako logic
  base:
    url: [https://github.com/gevako-nl/firmware](https://github.com/gevako-nl/firmware)
    ref: main
    file: packages/rs-base.yaml
    
  # 3. Load the preferred connectivity (WiFi or Thread)
  connectivity:
    url: [https://github.com/gevako-nl/firmware](https://github.com/gevako-nl/firmware)
    ref: main
    file: packages/rs-wifi.yaml
