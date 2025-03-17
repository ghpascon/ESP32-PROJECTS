// inputs
#define emg_pin 4
bool emg = false;

#define sensor_in_pin 5
#define sensor_out_pin 6

bool sensor_in = false;
bool sensor_out = false;

#define p1_close_pin 7
#define p1_open_pin 15
#define p2_close_pin 16
#define p2_open_pin 17

bool p1_close = false;
bool p1_open = false;
bool p2_close = false;
bool p2_open = false;

// outputs
#define motor_pin 39
#define motor_reverse_pin 40

bool motor = false;
bool motor_reverse = false;

#define speed_1_pin 41
#define speed_2_pin 42

extern byte speed;

extern bool read_on;

extern String status_msg;
extern String box_num;
extern int box_qtd;

extern bool box_inside;
extern byte door_mode;

extern const int client;

extern int current_retry_cnt;
extern byte retry;
extern USBCDC X714_USB;
