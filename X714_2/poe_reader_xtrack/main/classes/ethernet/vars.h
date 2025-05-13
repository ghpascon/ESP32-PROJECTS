extern bool eth_connected;
bool dhcp = true;

String esp_hostname = "esp32-ethernet";
extern String url;

#include <WiFi.h>
#include <AsyncHTTPRequest_Generic.h>
AsyncHTTPRequest *request = new AsyncHTTPRequest();
bool posted = false;
extern TAG tags[];
extern int current_tag;
extern TAG_COMMANDS tag_commands;

extern String esp_name;
