
extern const int max_tags;
extern TAG tags[];
extern int current_tag;

extern const int ant_qtd;
extern ANTENA antena[];

extern PINS pins;

extern bool read_on;
extern bool ignore_read;
extern String last_packs_read[];

extern bool always_send;

String tags_table = "";
extern MySerial myserial;
extern bool simple_send;