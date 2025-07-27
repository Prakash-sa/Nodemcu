# NodeMCU Firmware & Examples

This repository contains firmware, example scripts, and utilities for the [NodeMCU](https://nodemcu.readthedocs.io/en/release/) platform, supporting ESP8266, ESP8285, and ESP32 microcontrollers.

## 🚀 Features

- ✅ Pre-built NodeMCU firmware
- 📡 WiFi connectivity examples (STA/AP modes)
- 💡 GPIO control (e.g., LED blinking, sensor input)
- 🌐 Simple HTTP/WebSocket server scripts
- 🛠️ Customizable build options and flashing tools

# 🛠️ Getting Started
# 🔧 Prerequisites
ESP8266 or ESP32 board (e.g., NodeMCU DevKit)

USB-to-Serial driver (e.g., CP210x, CH340)

esptool.py or NodeMCU Flasher

Optional: Arduino IDE with ESP board support

# 💻 Flashing Firmware
Connect your board via USB

Pull GPIO0 low to enter flash mode (hold FLASH while pressing RESET)

Flash using esptool.py:

bash
Copy
Edit
esptool.py --port /dev/ttyUSB0 write_flash 0x00000 nodemcu-firmware.bin
Or use the GUI-based NodeMCU Flasher.


# 📚 Documentation
NodeMCU Firmware Docs

# 🤝 Contributing
Contributions are welcome! Feel free to:

Submit bug reports

Suggest improvements to scripts or documentation
