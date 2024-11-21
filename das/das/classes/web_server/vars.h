#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

extern byte door_mode;
extern byte mode;
extern byte speed;
extern byte retry;

extern bool motor;
extern bool motor_reverse;
extern bool cx_erro;
extern bool cx_ok;
extern bool read_on;
extern bool sensor_in;
extern bool sensor_out;
extern bool emg;

extern bool p1_close;
extern bool p1_open;
extern bool p2_close;
extern bool p2_open;

extern String box_num;
extern int box_qtd;