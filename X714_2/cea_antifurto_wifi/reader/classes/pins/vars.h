#define in_1_pin 2
#define in_2_pin 2
#define in_3_pin 2 

bool in_1 = false;
bool in_2 = false;
bool in_3 = false;

extern bool gpi_start;
extern bool read_on;

extern int gpi_stop_delay;

extern const int ant_qtd;
const int led_ant_pin[] = {1, 2, 2, 2};
const int led_ant_time = 1000;
unsigned long current_led_ant_time[] = {-1000, 0, 0, 0};

const int gpo_qtd = 3;
const int gpo_pin[gpo_qtd] = {2, 2, 2};
bool gpo[gpo_qtd] = {false, false, false};

extern bool connected;

const int wifi_led[3] = {5, 6, 7};
const int output_on_tags = 15;

const int config_pin = 4;
extern bool config_mode;
extern bool setup_done;
