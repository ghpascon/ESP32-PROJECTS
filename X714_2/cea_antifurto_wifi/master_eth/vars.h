ETHERNET_ESP ethernet_esp;
WEB_SERVER_ESP web_server_esp;
PINS pins;
CONFIG_FILE config_file_commands;

#define WATCHDOG_TIMEOUT 5

const int row = 4;
const int col = 4;
int ip_config[row][col];

String url = "http://192.168.10.1:5000/post";