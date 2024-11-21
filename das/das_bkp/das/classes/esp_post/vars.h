#include <WiFi.h>
// #include <AsyncHTTPRequest_Generic.h>
// AsyncHTTPRequest *request = new AsyncHTTPRequest();
#include <HTTPClient.h>
HTTPClient http;

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

const char *ssid = "SmartXcomercial";
const char *wifi_password = "Smtx321$";
// const String url = "http://192.168.0.157:5000/post";
const String url = "http://192.168.0.157:5107";

bool posted = false;
bool connected = false;