#define surge_pin 36
#define dps_pin 39
#define setup_pin 35

bool surge = false;
bool dps = false;

#define out_dps 12

extern int device_state;
extern int total_surge_cnt;
extern String total_surge;

extern bool setup_mode;

extern String api_status;
