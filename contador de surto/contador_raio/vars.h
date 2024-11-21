TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define WATCHDOG_TIMEOUT 5

#define start_mode_pin 27
#define send_pin 22

bool config_mode = false;
unsigned int reset_config_time = 300000;

bool connected = false;
String display_post_response = "";

int lightning_to_send = 0;
String total_lightning = "---";

//parametros web
String nome;
String rede;
String senha;
String api;
bool manut_status_ok;