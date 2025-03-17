SERIAL_PORT serial_port;

bool dhcp = true;

ETHERNET_ESP ethernet_esp;
bool connected = false;

PINS pins;

OUTPUT_SURGE output_surge;

CONFIG_FILE config_file_commands;

ESP_POST esp_post;


#define WATCHDOG_TIMEOUT 10

// variaveis globais
bool setup_mode = false;

bool online = false;
String api_status = "00";
String total_surge = "---";
int total_surge_cnt = 0;
int device_state = 0;
String display_message = "Surge Counter 2024";

bool need_post = false;

int qtd_raios = 0;

String nome;
String rede;
String senha;
String url;
String tipo;
String id_cliente;
String Authorization;

// String api = "http://52.67.141.45:8080/ws/sensors/sendSensorInformation";

LIGHTNING_SENSOR lightning_sensor;
byte lightning_distance = 0x00;