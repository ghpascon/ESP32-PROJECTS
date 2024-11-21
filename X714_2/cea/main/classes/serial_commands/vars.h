#define tx_reader_module 13
#define rx_reader_module 14

extern READER reader_module;

extern const bool debug_mode;

extern bool read_on;

extern TAG_COMMANDS tag_commands;

bool write_tag_on=false;
String current_epc;
String new_epc;
String password;

extern bool answer_rec;

extern ANTENA_COMMANDS antena_commands;
