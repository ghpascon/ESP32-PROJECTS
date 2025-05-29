#define in_1_pin 41
#define in_2_pin 40
#define in_3_pin 39

bool in_1 = false;
bool in_2 = false;
bool in_3 = false;

extern bool gpi_start;
extern bool read_on;

extern int gpi_stop_delay;

extern const int ant_qtd;
const int led_ant_pin[] = {18, 17, 16, 15};

const int gpo_qtd = 3;
const int gpo_pin[gpo_qtd] = {20, 19, 8};
bool gpo[gpo_qtd] = {false, false, false};

extern const bool simple_send;

extern bool setup_done;
extern bool read_on;
extern String status_value;
extern bool eth_connected;

extern int current_tag;
extern unsigned long buzzer_time;
extern byte buzzer_vol;
extern bool buzzer_on;
