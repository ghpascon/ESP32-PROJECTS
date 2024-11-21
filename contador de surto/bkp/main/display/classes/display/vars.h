#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// variaveis
extern bool online;
extern String api_status;
extern String total_surge;
extern int device_state;
extern String display_message;
extern bool password_ok;

//  lvlg
lv_obj_t *screen_main;
lv_obj_t *device_state_obj;

lv_obj_t *screen_inspec;

lv_obj_t *screen_emg;

String password = "";
String secret = "1111";
bool wrong_password = false;