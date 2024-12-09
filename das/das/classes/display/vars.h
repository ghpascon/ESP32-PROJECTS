#include <UnicViewAD.h>
LCM Lcm(Serial2);

LcmVar mode_buttons(0);
extern byte mode;

LcmVar door_mode_buttons(1);
LcmVar door_mode_display(2);
extern byte door_mode;

LcmVar retry_buttons(3);
LcmVar retry_display(4);
extern byte retry;
extern const byte retry_interval[];

LcmVar speed_buttons(5);
LcmVar speed_display(6);
extern byte speed;
extern const byte speed_interval[];

LcmVar cfg_button(7);

LcmVar state_icon(8);

LcmString display_instruction_label(100, 100);
extern const String instruction_messages[];
extern String state_msg;

LcmString display_box_label(200, 100);
extern String box_num;
extern int box_qtd;

LcmString display_status_label(300, 100);
LcmString display_status_label_2(400, 100);

extern SERIAL_PORT serial_port;

extern byte step;

extern bool emg;
extern bool box_inside;
extern byte door_mode;
extern bool read_on;

extern bool cx_ok;
extern bool cx_erro;

extern const bool debug_mode;

extern bool readed;

extern bool p1_close;
extern bool p1_open;
extern bool p2_close;
extern bool p2_open;


extern bool motor;
extern bool motor_reverse;

extern bool sensor_in;
extern bool sensor_out;

extern String status_msg;
