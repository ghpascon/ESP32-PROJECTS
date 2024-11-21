#if ESP_ARDUINO_VERSION < ESP_ARDUINO_VERSION_VAL(3, 0, 0)
#include <ETHClass2.h>
#define ETH ETH2
#else
#include <ETH.h>
#endif
#include <SPI.h>
#include <WiFi.h>