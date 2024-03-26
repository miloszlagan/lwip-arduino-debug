// Copyright (c) 2024 Husarnet sp. z o.o.
// Authors: listed in project_root/README.md
// License: specified in project_root/LICENSE.txt

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_check.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "protocol_examples_common.h"

#include "Arduino.h"
#include "husarnet.h"

static const char *TAG = "main";

void start_webserver_idf();
void start_webserver_arduino();

extern "C" void app_main(void) {
    initArduino();
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    // Initialize WiFi or Ethernet, depending on the menuconfig configuration.
    ESP_ERROR_CHECK(example_connect());
    // In order to reduce ping, power saving mode is disabled
    esp_wifi_set_ps(WIFI_PS_NONE);

    ESP_LOGI(TAG, "Starting Husarnet client...");

    // Initialize Husarnet client
    HusarnetClient* client = husarnet_init();

    // This function joins the network and blocks until the connection is established
    // Use join code obtained from the Husarnet Dashboard
    husarnet_join(client, "husarnet-esp32", "XXXXXXXXXXX");

    // Print the Husarnet address
    char ip[16];
    husarnet_get_ip_address(client, ip, sizeof(ip));
    ESP_LOGI(TAG, "Husarnet IP address: %s", ip);

    // Print local IP address
    esp_netif_ip_info_t ip_info;
    esp_netif_get_ip_info(esp_netif_get_handle_from_ifkey("WIFI_STA_DEF"), &ip_info);
    ESP_LOGI(TAG, "Local IP address: " IPSTR, IP2STR(&ip_info.ip));

    // Start the web server
    start_webserver_idf();
    start_webserver_arduino();

    while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
