AsyncWebServer server(80);

const int max_commands = 1000;
String last_commands[max_commands];
int current_cmd = 0;

AsyncHTTPRequest *request = new AsyncHTTPRequest();

extern String url;

bool posted = false;
extern bool eth_connected;

extern CONFIG_FILE config_file_commands;

extern int ip_config[4][4];

String IP;
String GATEWAY;
String SUBNET;
String DNS;