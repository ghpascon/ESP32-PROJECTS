// vars
#include <WiFi.h>
#include <HTTPClient.h>

extern bool eth_connected;
bool dhcp = true;

extern String url;

extern TAG tags[];
extern int current_tag;
extern TAG_COMMANDS tag_commands;

extern String esp_name;
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
extern const int max_tags;
bool posted = false;

String payload = "";