#define led_vermelho 15
#define led_verde 16
#define led_azul 17

#define in_1_pin 19
#define in_2_pin 19
#define in_3_pin 19

bool in_1 = false;
bool in_2 = false;
bool in_3 = false;

extern bool gpi_start;
extern bool read_on;

extern int gpi_stop_delay;

extern const int ant_qtd;
const int led_ant_pin[] = {41, 40, 19, 19};
const int led_ant_time = 200;
unsigned long current_led_ant_time[] = {0, 0, 0, 0};

const int gpo_qtd = 3;
const int gpo_pin[gpo_qtd] = {19, 19, 19};
bool gpo[gpo_qtd] = {false, false, false};

extern bool eth_connected;
extern bool setup_done;
