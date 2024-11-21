ESP32_DISPLAY lvlg_display;
SERIAL_PORT serial_port;
#define WATCHDOG_TIMEOUT 5

// variaveis globais
bool online = false;
String api_status = "";
String total_surge = "";
int device_state = 0;
String display_message = "";
bool password_ok = false;