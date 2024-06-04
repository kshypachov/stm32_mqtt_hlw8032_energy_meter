# STM32F401CE Firmware for Home Assistant Integration

## Overview

This project contains firmware designed to work with the STM32F401CE microcontroller. The firmware starts execution from address `0x08010000` and works in conjunction with a bootloader. The bootloader is necessary for updating the firmware from SPI Flash. You can use the bootloader provided in my repository or create your own.

## Features

- **Home Assistant Integration via MQTT**: The module can be connected to Home Assistant (HA) using MQTT without requiring any additional integrations.
- **Data Parameters**: The module provides several data parameters, read from the HLW8032 sensor:
  - Voltage
  - Current
  - Energy
  - Power Factor
  - Active Power
  - Apparent Power (calculated as Voltage * Current)
- **Persistent Storage**: The module stores energy data into Flash memory between reboots or power-offs.

## Getting Started

### Prerequisites

- STM32F401CE microcontroller
- HLW8032 sensor
- Home Assistant setup with MQTT integration
- SPI Flash for firmware updates

### Installation

1. **Bootloader**: Ensure the bootloader is flashed at the correct location. You can use the provided bootloader from this repository or write your own.
2. **Firmware**: Flash the firmware to address `0x08010000` on the STM32F401CE microcontroller.
3. **Home Assistant Configuration**:
   - Set up MQTT in Home Assistant.
   - Configure the module to connect to your MQTT broker.

### Usage

Once the module is set up and connected to Home Assistant via MQTT, it will start sending the following data parameters:

- **Voltage**
- **Current**
- **Energy**
- **Power Factor**
- **Active Power**
- **Apparent Power**

These values can be monitored and used in Home Assistant for various automations and monitoring tasks.



## Contributing

Contributions are welcome! Please fork this repository and submit pull requests with your improvements.

## License

This project is licensed under the MIT License. See the LICENSE file for more details.

## Contact

For any questions or issues, please open an issue in this repository or contact me directly.

