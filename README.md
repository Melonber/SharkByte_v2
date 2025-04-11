# EvilTwin Wi-Fi Captive Portal Project 
*ESP32-C3 based rogue access point with credential harvesting*

## Table of Contents
- [Features](#-features)
- [Hardware Requirements](#-hardware-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Code Structure](#-code-structure)
- [Legal Disclaimer](#⚠️-legal-disclaimer)
- [License](#-license)

## 🚀 Features

### Core Functionality
- **Rogue AP Creation**  
  Instantly creates open "Free_Public_WiFi" access point
- **Automatic Redirection**  
  Forces captive portal on all HTTP requests
- **Credential Harvesting**  
  Captures and displays submitted credentials on OLED

### Technical Highlights
- **Multi-Device Support**  
  Special handling for both Android and iOS devices
- **Real-time Monitoring**  
  Shows connected clients on OLED display
- **Simple UI**  
  3-button control interface with intuitive menu

## 🔧 Hardware Requirements

| Component | Specifications | Connection |
|-----------|---------------|------------|
| ESP32-C3 DevKit | ESP32-C3-WROOM-02 | - |
| OLED Display | SH1106 128x64 | SDA:GPIO4, SCL:GPIO5 |
| Tactile Buttons | 6x6mm | Select:GPIO3, Down:GPIO1, Up:GPIO2 |

## 📥 Installation

### Prerequisites
- PlatformIO IDE (VS Code extension)
- ESP32-C3 USB drivers

### Setup Process
1. Clone repository:
   ```bash
   git clone https://github.com/yourrepo/EvilTwin-ESP32.git
2. Install dependencies: 
   ```bash
   pio lib install "Adafruit SH110X"
   pio lib install "ESPAsyncWebServer-esphome"  
3. Flash firmware:
   ```bash
   pio run --target upload

### Key Components:
- **DNSServer: Handles all DNS spoofing**
- **AsyncWebServer: Manages HTTP traffic**
- **SH1106G: OLED display controller**

## ⚠️ Legal Disclaimer
Warning: This project demonstrates security vulnerabilities for educational purposes only. Unauthorized use on networks you don't own is illegal. The creator disclaims all responsibility for misuse.