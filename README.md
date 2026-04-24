<div align="center">

# ⚡ Gevako ESPHome Firmware

### *Official firmware repository for Gevako Industrial Grade Smart Home Hardware*

<a href="https://www.gevako.com/" target="_blank">🏠 Home</a> • <a href="https://www.gevako.com/shop/" target="_blank">🛒 Store</a> • <a href="https://www.gevako.com/support/" target="_blank">📖 Documentation</a> • <a href="https://www.youtube.com/@gevako" target="_blank">🎥 Tutorials</a>

![Microcontroller](https://img.shields.io/badge/MCU-ESP32--C6-black?style=for-the-badge)
![Connectivity](https://img.shields.io/badge/Connectivity-WiFi_6_|_Thread-blue?style=for-the-badge)
![ESPHome](https://img.shields.io/badge/Firmware-ESPHome-000000?style=for-the-badge&logo=esphome&logoColor=white)
![Home Assistant](https://img.shields.io/badge/Integration-Home_Assistant-41BDF5?style=for-the-badge&logo=home-assistant&logoColor=white)

</div>

---

## 📖 Overview

Welcome to the official firmware repository for Gevako B.V. hardware. This repository contains all the open-source ESPHome configuration files required to run, provision, and customize your Gevako Smart Relay boards.

Our hardware is built around the **ESP32-C6 (RISC-V)**, providing rock-solid, 100% local control via **WiFi 6** or **Thread**, seamlessly integrating with Home Assistant. No cloud dependencies, no proprietary lock-in.

---

## 📂 Repository Structure

We use a modular approach to keep our firmware clean, maintainable, and easy to update. The repository is divided into the following directories:

### 1. Hardware Configurations
These directories contain the base YAML files and documentation specific to each physical board. If you are looking to fork or view the exact configuration of your device, start here:
* 🎚️ **[`/rs5`](rs5/)** - Firmware and documentation for the **Gevako RS5** (5-Channel Smart Relay, Common Source).
* 🎛️ **[`/rs6`](rs6/)** - Firmware and documentation for the **Gevako RS6** (6-Channel Smart Relay, Independent).

### 2. Core Packages
* 📦 **[`/packages`](packages/)** - The engine of our firmware. This directory contains the shared logic, hardware pinouts, and connectivity stacks (WiFi and Thread). The hardware YAML files automatically import these modular packages. Read more in the [Packages README](packages/README.md).

---

## 🚀 Getting Started & Provisioning

All Gevako boards ship with ESPHome pre-installed. You can seamlessly provision them to your network using our web tools via USB.

* **WiFi Setup & Flashing:** Use the [Gevako ESPHome Installer](https://www.gevako.com/esphome/) to connect the relay to your WiFi network or install custom firmware updates.
* **Thread Setup:** Use the [Gevako Thread TLV Tool](https://www.gevako.com/thread/) to inject your Home Assistant Thread network credentials directly into the device via USB.

To add a provisioned device to Home Assistant, simply navigate to **Settings > Devices & services** and the device will appear under the ESPHome integration.

---

## 🛠️ Customizing the Firmware

Since our firmware is based on ESPHome, you have full control. You can use our files as a starting point and add your own automations, sensors, or logic.

1. Create a new device in your ESPHome dashboard.
2. Copy the content of the `gevako-rs5.yaml` or `gevako-rs6.yaml` file into your configuration.
3. Modify the `substitutions` block to fit your naming conventions.
4. Flash the device Over-The-Air (OTA) or via USB.

The firmware will automatically pull the necessary underlying logic from the `packages/` directory in this repository.

---

## 🤝 Support & Community

We believe in open-source collaboration. Feel free to explore the code, report issues, or suggest improvements.

- 🐛 **Found a bug?** Open an issue right here on GitHub.
- 💬 **Need help?** Visit our [Customer Support page](https://www.gevako.com/contact/).
- 📧 **Engineering:** <a href="mailto:info@gevako.com">info@gevako.com</a>

---

<div align="center">
<b>License:</b> MIT License (see <a href="LICENSE">LICENSE</a> file) <br>
<i>Gevako B.V. • CoC: 93569882 • Designed & Assembled in the Netherlands 🇳🇱</i>
</div>
