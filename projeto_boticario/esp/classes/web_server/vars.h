#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);

#include <AsyncTCP.h>
#include <Update.h>

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

extern bool box_inside ;
extern const bool debug_mode;
