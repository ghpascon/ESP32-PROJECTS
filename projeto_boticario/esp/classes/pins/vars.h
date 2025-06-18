// inputs
#define emg_pin 4
bool emg = false;

#define sensor_in_pin 5
#define sensor_out_pin 6

bool sensor_in = false;
bool sensor_out = false;


#define r700_ok_pin 16
#define r700_erro_pin 17

bool r700_ok = false;
bool r700_erro = false;

// outputs
#define motor_pin 39
#define motor_reverse_pin 40

bool motor = false;
bool motor_reverse = false;

#define speed_1_pin 41
#define speed_2_pin 42

extern byte speed;

#define r700_read_pin 15


extern bool read_on;

extern String status_msg;

extern bool box_inside;

extern int current_retry_cnt;
extern byte retry;

extern bool cx_ok;
extern bool cx_erro;