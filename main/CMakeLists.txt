idf_component_register(SRCS "main.cpp" "webserver_idf.cpp" "webserver_arduino.cpp"
                    INCLUDE_DIRS "."
                    REQUIRES esp_husarnet esp_wifi esp_http_server arduino-esp32 ESPAsyncWebServer)
