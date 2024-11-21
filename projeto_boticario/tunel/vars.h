bool integrated = false;

// pins
PINS pins;

//web server
WEB_SERVER web_server;

//SERIAL
SERIAL_PORT serial_port;

//WATCHDOG
#define WATCHDOG_TIMEOUT 5

//config
CONFIG_FILE config_file_commands;

//motor state
MOTOR_STATE motor_state;

//led rgb
LED_RGB led_rgb;

// variaveis globais
bool cx_ok = false;
bool cx_erro = false;

int speed = 1;
int retry_cnt = 0;

bool read_on = false;