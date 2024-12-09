const bool debug_mode = false;
const bool integrated = true;

#define WATCHDOG_TIMEOUT 5

SERIAL_PORT serial_port;
LCM_DISPLAY lcm_display;
CONFIG_FILE config_file_commands;
PINS pins;
MOTOR_STATE motor_state;
WEB_SERVER web_server;
LED_RGB led_rgb;

byte mode = 0x00;

byte retry = 0x00;
const byte retry_interval[2] = {0, 10};

byte speed = 0x00;
const byte speed_interval[2] = {1, 4};

bool read_on = false;
bool cx_ok = false;
bool cx_erro = false;

byte door_mode = 1;

String box_num = "";
int box_qtd = 0;

String instruction_label = "";
const String instruction_messages[] = {
    "EMERGENCIA ATIVADA!!!",
    "AGUARDANDO LEITURA \nDO CODIGO DE BARRAS",
    "COLOQUE A CAIXA\nNO TUNEL",
    "FECHE A PORTA\nDE ENTRADA",
    "FECHE AS PORTAS\nDE ENTRADA E DE SAIDA",
    "CONFERINDO A CAIXA...",
    "CAIXA APROVADA!",
    "CAIXA REPROVADA",
    "ABRA AS PORTAS"
};
String state_msg = "";

byte step = 0;

bool readed = false;

int answer_timeout = 10000;

String status_msg = "";
