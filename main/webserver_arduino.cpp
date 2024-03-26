#include "esp_log.h"

#include "Arduino.h"
#include "AsyncTCP.h"
#include "ESPAsyncWebServer.h"

static const char *TAG = "webserver";

AsyncWebServer server(8080);

void start_webserver_arduino() {
  ESP_LOGI(TAG, "Starting Arduino server on port 8080");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, Husarnet!");
  });
  server.begin();
}