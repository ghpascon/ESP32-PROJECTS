#define tx_reader_module 13
#define rx_reader_module 14 

#define tx_x714 19
#define rx_x714 20

extern READER reader_module;

extern const bool debug_mode;
extern const bool one_ant;

extern bool read_on;
bool last_read_on = false;

extern TAG_COMMANDS tag_commands;

bool write_tag_on = false;
String current_epc;
String new_epc;
String password;

extern bool answer_rec;

extern ANTENA_COMMANDS antena_commands;

extern bool start_reading;
extern bool gpi_start;
extern int gpi_stop_delay;
extern bool ignore_read;
extern bool always_send;

extern const byte min_power;
extern const byte max_power;
extern const byte min_rssi;
extern byte session;
extern byte max_session;