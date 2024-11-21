#define WATCHDOG_TIMEOUT 5

SERIAL_PORT serial_port;
LCM_DISPLAY lcm_display;
CONFIG_FILE config_file_commands;
ESP_POST esp_post;

byte mode = 0x00;

byte retry = 0x00;
const byte retry_interval[2] = {0, 10};

byte speed = 0x00;
const byte speed_interval[2] = {0, 4};

int password = 1234;

byte ant_cfg[4][2];
const byte power_interval[2] = {5, 30};
const byte rssi_interval[2] = {0, 130};
