#define surge_pin 27
#define dps_pin 26
#define setup_pin 25

bool surge = false;
bool dps = false;

#define out_dps 33

extern int device_state;
extern int total_surge_cnt;
extern String total_surge;

extern bool setup_mode;

extern String api_status;
