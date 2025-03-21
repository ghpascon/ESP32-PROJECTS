#include "USB.h"
USBCDC X714_USB;

#define tx2_pin 1
#define rx2_pin 2

extern byte mode;
extern byte retry;
extern byte speed;
extern byte door_mode;

extern byte step;
extern String box_num;
extern int box_qtd;

extern bool cx_ok;
extern bool cx_erro;

extern String state_msg;

extern const bool debug_mode;
extern const int results_qtd;
extern int box_results[];

extern const int client;