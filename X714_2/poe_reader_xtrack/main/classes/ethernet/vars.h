extern bool eth_connected;
bool dhcp = true;

String esp_hostname = "esp32-ethernet";
extern String url;

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
WiFiClientSecure client;
HTTPClient https;

extern TAG tags[];
extern int current_tag;
extern TAG_COMMANDS tag_commands;

extern String esp_name;
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
extern const int max_tags;
String tags_to_post[1000][2];
bool posted = false;