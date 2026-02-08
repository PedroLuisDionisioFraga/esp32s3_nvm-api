# NVM Driver Example

This example demonstrates how to use the NVM (Non-Volatile Memory) driver component for ESP32.

## How to use this example

### Hardware Required

* Any ESP32 development board

### Configure the project

No special configuration is required for this example.

### Build and Flash

Build the project and flash it to the board, then run the monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(Replace PORT with the name of the serial port to use.)

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

## Example Output

```
I (xxx) NVM Example: Key 'example_key' not found in NVS, default value: 0
I (xxx) NVM Example: Value written (example_key) to NVS: 12345
I (xxx) NVM Example: Value read (example_key): 12345
I (xxx) NVM Example: Key 'example_key' erased from NVS
I (xxx) NVM Example: Value read (example_key) after erasure: 0
I (xxx) NVM Example: Value written to NVS: 86554
I (xxx) NVM Example: Value written to NVS: 45874
I (xxx) NVM Example: Value read (example_key2): 86554
I (xxx) NVM Example: Value read (example_key3): 45874
I (xxx) NVM Example: Value read after erasure: 0
I (xxx) NVM Example: Value read after erasure: 0
```

## Functionality Overview

The example demonstrates the following NVM operations:

1. **Initialize** - Initialize the NVM driver
2. **Read** - Read a value from NVS (returns 0 if key doesn't exist)
3. **Write** - Write a value to NVS
4. **Erase** - Erase a specific key from NVS
5. **Erase All** - Erase all keys from NVS
6. **Restart** - Restart the ESP32 to verify persistence

## Supported Targets

* ESP32
* ESP32-S2
* ESP32-S3
* ESP32-C3
* ESP32-C6
* ESP32-H2
* ESP32-C2
* ESP32-C5
* ESP32-P4
