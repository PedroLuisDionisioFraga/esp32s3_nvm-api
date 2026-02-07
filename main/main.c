/* Non-Volatile Storage (NVS) Read and Write a Value - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <esp_log.h>
#include <esp_system.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <inttypes.h>

#include "nvm_api.h"

void app_main(void)
{
  nvm_init();
  uint32_t value = 0;

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Read a value to NVS
  nvm_read("example_key", (uint32_t *)&value);
  if (value == 0)
    ESP_LOGI("NVM Example", "Key 'example_key' not found in NVS, default value: %lu", value);
  else
    ESP_LOGI("NVM Example", "Value read from NVS: %lu", value);

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
                                          // Write a value to NVS
  // nvm_write("example_key", 12345);
  ESP_LOGI("NVM Example", "Value written (example_key) to NVS: %d", 12345);

  // Read the value back from NVS
  nvm_read("example_key", (uint32_t *)&value);
  ESP_LOGI("NVM Example", "Value read (example_key): %lu", value);

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Erase a key from NVS
  // nvm_erase("example_key");
  ESP_LOGI("NVM Example", "Key 'example_key' erased from NVS");

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Read the value again to confirm erasure
  nvm_read("example_key", (uint32_t *)&value);
  ESP_LOGI("NVM Example", "Value read (example_key) after erasure: %lu", value);

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Write others values to NVS
  // nvm_write("example_key2", 86554);
  ESP_LOGI("NVM Example", "Value written to NVS: %d", 86554);
  // nvm_write("example_key3", 45874);
  ESP_LOGI("NVM Example", "Value written to NVS: %d", 45874);

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Read the new values
  nvm_read("example_key2", &value);
  ESP_LOGI("NVM Example", "Value read (example_key2): %lu", value);
  nvm_read("example_key3", &value);
  ESP_LOGI("NVM Example", "Value read (example_key3): %lu", value);

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization

  // Erase all keys from NVS
  ////nvm_erase_all();

  vTaskDelay(3000 / portTICK_PERIOD_MS);  // Wait for NVS initialization
  // Read the erased values
  nvm_read("example_key2", (uint32_t *)&value);
  ESP_LOGI("NVM Example", "Value read after erasure: %lu", value);
  nvm_read("example_key3", (uint32_t *)&value);
  ESP_LOGI("NVM Example", "Value read after erasure: %lu", value);

  esp_restart();  // Restart the system to apply changes
}
