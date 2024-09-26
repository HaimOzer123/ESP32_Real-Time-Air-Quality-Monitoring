# Real-Time Air Quality Monitoring System

### Author: Haim Ozer

This project is designed to monitor air quality in real-time using the **ESP32-WROOM-32D** microcontroller. The system utilizes I2C sensors to measure CO2 levels, temperature, and humidity, and displays the data on a 16x2 LCD screen. It is designed to demonstrate real-time data collection, processing, and display in an embedded environment. Additionally, motion detection can be incorporated to trigger data.

## Project Overview

This system monitors the following environmental conditions:
- **CO2 Levels**: Using the ENS160 sensor.
- **Temperature & Humidity**: Using the AHT21 sensor.
- **Display**: Information is displayed on a 16x2 I2C LCD screen.

### Video Presentation:
Watch the video presentation of the project for an overview of the real-time air quality monitoring system in action.
Check out the [video presentation of the project](https://drive.google.com/file/d/13vhrw3RD76HinZ9N-YI6pjBKKC9hIGsp/view?usp=sharing).

### Wiring Diagram:
wiring images on the breadboard to understand how the components are physically connected.
Check out the [wiring images](https://drive.google.com/file/d/10cAnoR2bWLvjFiA64zY_UB2dPf7xNp7n/view?usp=sharing).

### Technologies Used:
- **ESP32-WROOM-32D** microcontroller for real-time data processing
- **C++** for firmware development
- **PlatformIO** IDE integrated with **VS Code**
- **Arduino Core** for ESP32
- **I2C Communication** for sensor data transfer
- Real-time environmental monitoring

### Real-Time Embedded Software Concepts:
- **Real-Time Data**: The system continuously collects sensor data and updates the LCD display in real-time.
- **Sensor Integration and I2C Communication**: The ENS160 and AHT21 sensors are connected via I2C, demonstrating proficiency in interfacing with multiple sensors on the same communication bus.
- **Efficient Resource Management**: The project showcases resource-efficient coding to ensure timely sensor reads, data updates, and power management.
- **Real-Time Debugging and Optimization**: Serial output is used for real-time debugging, a key skill in embedded software engineering.

This project highlights key skills applicable to **real-time embedded systems** and **low-level programming**.

### Libraries Required:
To run this project, make sure the following libraries are installed:
1. **ScioSense_ENS160** (`ScioSense_ENS160.h`) for the ENS160 CO2 sensor.
2. **Adafruit AHT10/AHT20/AHT21** (`Adafruit_AHTX0.h`) for the AHT21 temperature and humidity sensor.
3. **LiquidCrystal_I2C** for the LCD display.
4. **Wire.h** for I2C communication.

### Hardware Setup:
Here is the pin configuration for connecting the sensors to the ESP32:

| Component    | SDA Pin | SCL Pin | Other Pins    |
|--------------|---------|---------|---------------|
| **ENS160**   | D12     | D13     | ADD = D14, CS = D27, NT = D26 |
| **AHT21**    | D12     | D13     | -             |
| **LCD I2C**  | D4      | D16     | -             |

### Installation and Setup Guide:

1. **PlatformIO Setup:**
   - Install [PlatformIO](https://platformio.org/install) in Visual Studio Code.
   - Open VS Code, navigate to the Extensions tab, and search for "PlatformIO IDE."
   - Install the extension and restart VS Code.
   
2. **Cloning the Project:**
   Clone this repository or copy the source code into your local machine.

3. **Library Installation:**
   PlatformIO automatically resolves libraries. Ensure your `platformio.ini` contains the correct dependencies:
   ```ini
   [env:esp32]
   platform = espressif32
   board = esp32dev
   framework = arduino
   lib_deps =
       adafruit/Adafruit AHT10/AHT20/AHT21@^1.2.0
       ScioSense_ENS160
       LiquidCrystal_I2C
