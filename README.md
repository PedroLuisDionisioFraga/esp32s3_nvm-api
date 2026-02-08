# ESP32 NVM Driver

A simple and efficient Non-Volatile Memory (NVM) driver for ESP32 microcontrollers, built on top of the ESP-IDF NVS (Non-Volatile Storage) library. This component provides a straightforward API for storing and retrieving persistent data across device reboots.

## Features

- ✅ Simple API for NVM operations (read, write, erase)
- ✅ Built on top of ESP-IDF NVS library
- ✅ Automatic NVS initialization with error handling
- ✅ Support for `uint32_t` data type
- ✅ Bulk erase functionality
- ✅ Comprehensive error logging
- ✅ Tested on ESP32-S3

## Installation

### Using ESP Component Registry

Add the component to your project using the IDF Component Manager:

```bash
idf.py add-dependency "pedroluisdionisiofraga/nvm-api^1.0.0"
```

### Manual Installation

1. Clone this repository into your project's `components` directory:

```bash
cd your_project/components
git clone https://github.com/PedroLuisDionisioFraga/esp32s3_nvm-api.git nvm_driver
```

2. The component will be automatically detected by ESP-IDF build system.

## Requirements

- ESP-IDF version 5.0 or higher
- ESP32, ESP32-S2, ESP32-S3, ESP32-C3, or other ESP32 variants

## Usage

### Basic Example

```c
#include "nvm_api.h"
#include <esp_log.h>

void app_main(void)
{
    // Initialize NVM
    nvm_init();

    uint32_t value = 0;

    // Write a value to NVM
    nvm_write("my_key", 12345);

    // Read the value back
    nvm_read("my_key", &value);
    ESP_LOGI("APP", "Value read: %lu", value);

    // Erase a specific key
    nvm_erase("my_key");

    // Erase all keys (use with caution)
    // nvm_erase_all();
}
```

### Persistent Configuration Example

```c
#include "nvm_api.h"
#include <esp_log.h>

void save_wifi_config(uint32_t reconnect_count)
{
    nvm_write("wifi_reconnects", reconnect_count);
}

uint32_t load_wifi_config(void)
{
    uint32_t count = 0;
    nvm_read("wifi_reconnects", &count);
    return count;
}

void app_main(void)
{
    nvm_init();

    // Load previous configuration
    uint32_t reconnects = load_wifi_config();
    ESP_LOGI("APP", "Previous reconnect count: %lu", reconnects);

    // Increment and save
    reconnects++;
    save_wifi_config(reconnects);

    ESP_LOGI("APP", "New reconnect count: %lu", reconnects);
}
```

## API Reference

### `void nvm_init(void)`

Initializes the NVS flash partition. This function must be called before any other NVM operations.

**Behavior:**
- Automatically handles partition truncation and version mismatches
- Erases and reinitializes NVS if necessary

**Example:**
```c
nvm_init();
```

---

### `void nvm_write(const char *key, uint32_t value)`

Writes a `uint32_t` value to NVM with the specified key.

**Parameters:**
- `key`: Null-terminated string (max 15 characters)
- `value`: 32-bit unsigned integer to store

**Example:**
```c
nvm_write("boot_count", 42);
```

---

### `void nvm_read(const char *key, uint32_t *value)`

Reads a `uint32_t` value from NVM using the specified key.

**Parameters:**
- `key`: Null-terminated string (max 15 characters)
- `value`: Pointer to store the retrieved value

**Behavior:**
- Sets `*value = 0` if the key is not found

**Example:**
```c
uint32_t count = 0;
nvm_read("boot_count", &count);
```

---

### `void nvm_erase(const char *key)`

Erases a specific key-value pair from NVM.

**Parameters:**
- `key`: Null-terminated string (max 15 characters)

**Example:**
```c
nvm_erase("boot_count");
```

---

### `void nvm_erase_all(void)`

Erases all key-value pairs in the NVM namespace. **Use with caution!**

**Example:**
```c
nvm_erase_all();
```

## Understanding NVM Basics

Non-Volatile Memory (NVM) retains data even when the device is powered off. This makes it ideal for:
- Configuration settings
- Calibration data
- Usage statistics
- Device state information

### Keys and Values

- **Keys**: Case-sensitive, unique identifiers (max 15 characters)
- **Values**: Currently supports `uint32_t` (32-bit unsigned integers)

## Important Notes

1. **Flash Erase Warning**: If you flash your ESP32 with the `--erase-all` flag, all NVM data will be lost.
2. **Key Naming**: Choose descriptive, unique key names to avoid conflicts.
3. **Namespace**: All operations use the default `"storage"` namespace.
4. **Data Persistence**: Data persists across reboots and power cycles (unless flash is erased).

## Troubleshooting

### Values not persisting after reboot

**Possible causes:**
- Flashing with `--erase-all` flag (erases all flash including NVM)
- Calling `nvm_erase_all()` before reboot
- Power loss before `nvs_commit()` completes
- Missing NVS partition in partition table (default should work)

**Solution:**
- Flash without erase: `idf.py flash`
- Avoid calling `nvm_erase_all()` unless necessary
- Ensure stable power during write operations

### Key not found errors

**Solution:**
- Verify the key name matches exactly (case-sensitive)
- Check that the key was written before attempting to read
- Remember that `nvm_read()` returns 0 for missing keys

## Project Structure

```
esp32-nvm-driver/
├── components/
│   └── nvm_driver/
│       ├── CMakeLists.txt
│       ├── idf_component.yml
│       ├── nvm_api.c
│       ├── include/
│       │   └── nvm_api.h
│       └── README.md
├── main/
│   ├── CMakeLists.txt
│   └── main.c (example)
├── CMakeLists.txt
└── README.md
```

## License

This project is in the Public Domain or licensed under CC0, at your option.

Unless required by applicable law or agreed to in writing, this software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.

## References

- [ESP-IDF NVS Flash Documentation](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/storage/nvs_flash.html)
- [ESP-IDF NVS Example](https://github.com/espressif/esp-idf/tree/master/examples/storage/nvs/nvs_rw_value)
- [ESP Component Registry](https://components.espressif.com/)

## Author

**Pedro Luis Dionísio Fraga**\
📧 pedrodfraga@hotmail.com

---

![GitHub repo size](https://img.shields.io/github/repo-size/PedroLuisDionisioFraga/esp32_nvm-api?label=Repo%20Size&logo=Github&color=fedcba)
