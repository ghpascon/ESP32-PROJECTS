#include <WiFi.h>
#include <HTTPClient.h>
HTTPClient http;

String name = "Device-1";
String url = "https://lc-iot-hub.azure-devices.net/devices/{name}/messages/events?api-version=2016-02-03";

bool posted = false;

String Authorization = "SharedAccessSignature sr=lc-iot-hub.azure-devices.net%2Fdevices%2F{name}&sig=Iz5ai5TZb8HOF3wLzE18gsIAgRgJD4ou21KBkPtvRuM%3D&se=1772856482";

extern bool connected;

String tipo = "CONTADOR DE RAIO";
String id_cliente = "2";
String total_surge = "10";
int device_state = 0;
int qtd_raios = 2;