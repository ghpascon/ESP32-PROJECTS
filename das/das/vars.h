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
const byte door_mode_interval[2] = {1, 3};

String box_num = "";
int box_qtd = 0;

String instruction_label = "";
const String instruction_messages[] = {
    "EMERGENCY\nACTIVATED!!!",
    "ENTER THE BOX\nINFOS",
    "INSERT THE BOX\nTO PERFORM THE\nREADING!",
    "CLOSE THE ENTRY\nDOOR...",
    "CLOSE BOTH ENTRY\nAND EXIT DOORS...",
    "PERFORMING BOX\nREADING...",
    "BOX SUCCESSFULLY\nAPPROVED!!!",
    "BOX REJECTED\nXXX"};

byte step = 0;
