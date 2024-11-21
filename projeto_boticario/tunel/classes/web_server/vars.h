#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

extern int speed;
extern int retry_cnt;

extern bool motor;
extern bool motor_reverse;
extern bool cx_erro;
extern bool cx_ok;
extern bool read_on;
extern bool sensor_in;
extern bool sensor_out;
extern bool emg;