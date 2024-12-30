# SharkByte_V2 Project

Welcome to the **SharkByte_V2**, a compact and educational cybersecurity tool designed to simulate vulnerable Wi-Fi networks for research, learning, and testing purposes. This project uses the ESP32 microcontroller to create a honeypot that mimics a legitimate Wi-Fi network, attracting potential attackers and capturing insights into their behavior.

## Features

- **Wi-Fi Honeypot**: Creates an open Wi-Fi access point without a password to attract connections.
- **DNS Redirection**: All traffic is redirected to the ESP32, providing complete control over the user experience.
- **Customizable Login Page**: Hosts a simple login page where input credentials are captured for analysis.
- **OLED Display Integration**: Displays the network's IP address, connection status, and login attempts.
- **Compact Design**: Runs on an ESP32 microcontroller, making it lightweight and portable.

## How It Works

1. **Access Point Creation**: The ESP32 sets up an open Wi-Fi network without a password, making it appear as a public hotspot.
2. **DNS Redirection**: A DNS server intercepts all outgoing DNS queries and redirects them to the ESP32's IP address.
3. **Login Page Hosting**: A simple login page is hosted on the ESP32, allowing users to "log in."
4. **Data Collection**: Any credentials entered on the login page are captured and displayed via the Serial Monitor or OLED screen.
5. **OLED Feedback**: The current IP address, connected devices, and captured data are shown on the OLED display in real-time.

## Components

- **ESP32 Microcontroller**: The brain of the project.
- **1.3-inch OLED Display**: Displays important status information.
- **Push Buttons**: Navigate through the menu options.

## Menu Options

The project features an interactive menu accessible via buttons:

- **Wi-Fi Networks**: Scans and displays available Wi-Fi networks (future feature).
- **Deauth**: A placeholder for deauthentication functionality (future feature).
- **Start Honeypot**: Initiates the honeypot functionality.

## Prerequisites

- **Hardware**:
  - ESP32 Development Board
  - OLED Display (1.3-inch, I2C compatible)
  - Push Buttons (3 or more)

- **Software**:
  - Arduino IDE or PlatformIO
  - Required Libraries:
    - `WiFi.h`
    - `ESPAsyncWebServer.h`
    - `AsyncTCP.h`
    - `DNSServer.h`
    - `Adafruit_SSD1306.h`
    - `Adafruit_GFX.h`

## Setup and Installation

1. **Clone Repository**:
   ```bash
   git clone https://github.com/yourusername/honeypot-wifi
   ```

2. **Install Dependencies**:
   - Install the required libraries via the Arduino Library Manager or PlatformIO.

3. **Upload Code**:
   - Connect your ESP32 to your computer and upload the `main.cpp` file.

4. **Connect OLED Display**:
   - Use the following pin connections:
     - `VCC` -> 3.3V
     - `GND` -> GND
     - `SDA` -> GPIO 21
     - `SCL` -> GPIO 22

5. **Power On**:
   - Power the ESP32 via USB or a battery pack.
   - Before start to upload code to ESP32, type in terminal: `pio run --target uploadfs`

6. **Monitor Output**:
   - Open the Serial Monitor to view captured data and debug information.

## Legal Disclaimer

This project is intended solely for educational and research purposes. The creator is not responsible for any misuse of the project. Ensure compliance with all applicable laws and regulations in your region before deploying this tool.

## Contributing

I will appriciate contributions to improve this project! Feel free to submit issues or pull requests via the [GitHub repository]([https://github.com/yourusername/honeypot-wifi](https://github.com/Melonber/SharkByte_v2)).

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
