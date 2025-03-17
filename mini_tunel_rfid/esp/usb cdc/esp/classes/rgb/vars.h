#include <FastLED.h>
#define NUM_LEDS 1
#define DATA_PIN 48
CRGB leds[NUM_LEDS];

extern bool motor;
extern bool read_on;
extern bool cx_erro;
extern bool cx_ok;
extern bool emg;
