const bool debug_mode = false;

const bool one_ant = false;

const bool simple_send=false;
//pins
PINS pins;

//reader config
READER reader_module;

// Ethernet
ETHERNET_ESP ethernet_esp;
String url;
String esp_name;
// web server
WEB_SERVER web_server;

//tags
TAG_COMMANDS tag_commands;

const int max_tags = 1000;
TAG tags[max_tags];
int current_tag = 0;

//ant_config
const int ant_qtd = 4;
ANTENA antena[ant_qtd];
ANTENA_COMMANDS antena_commands;
const byte min_power = 5;
const byte max_power = 30;
// const byte max_power = one_ant ? 20 : 30;
const byte min_rssi = 40;

byte write_power = max_power;

// SERIAL
SERIAL_PORT serial_port;

//WATCHDOG
#define WATCHDOG_TIMEOUT 10

//config
CONFIG_FILE config_file_commands;

//reading
bool read_on = false;
byte session = 0x00;
byte max_session = 0x03;

//modes
bool start_reading = false;
bool gpi_start = false;
bool ignore_read = false;
bool always_send = false;

//LAST PACKS
LAST_PACKS last_packs;
const int max_packs = 10;
String last_packs_read[max_packs];

//global
byte temperatura = 0;
int gpi_stop_delay = 0;
String status_value = "";
bool eth_connected = false;
unsigned long buzzer_time = 0;
byte buzzer_vol = 0;