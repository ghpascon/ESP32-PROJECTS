const bool debug_mode = false;
const bool integrated = true;

#define WATCHDOG_TIMEOUT 10

SERIAL_PORT serial_port;
LCM_DISPLAY lcm_display;
CONFIG_FILE config_file_commands;
PINS pins;
MOTOR_STATE motor_state;
WEB_SERVER web_server;
LED_RGB led_rgb;

byte mode = 0x00;

byte retry = 0x00;
int current_retry_cnt = 0;
const byte retry_interval[2] = {0, 10};

byte speed = 0x00;
const byte speed_interval[2] = {1, 4};

bool read_on = false;
bool cx_ok = false;
bool cx_erro = false;


String instruction_label = "";
const String instruction_messages[] = {
    "EMERGENCIA ATIVADA!!!",
    "AGUARDANDO LEITURA \nDO CODIGO DE BARRAS",
    "COLOQUE A CAIXA\nNO TUNEL",
    "FECHE A PORTA\nDE ENTRADA",
    "FECHE AS PORTAS\nDE ENTRADA E DE SAIDA",
    "CONFERINDO A CAIXA...",
    "CAIXA APROVADA!",
    "CAIXA REPROVADA"};
String state_msg = "";

byte step = 0;

int answer_timeout = 10000;

String status_msg = "";

const int results_qtd = 3;
int box_results[results_qtd];
bool timeout = false;