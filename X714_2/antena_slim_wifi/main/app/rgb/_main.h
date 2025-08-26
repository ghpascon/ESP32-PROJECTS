#include <FastLED.h>
#include "vars.h"

class LED_RGB
{
public:
	void setup()
	{
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	}

	void state()
	{
		byte led_brigthness = 0x50;
		if (config_mode)
			leds[0] = CRGB(0x00, 0x00, led_brigthness);
		else if (!is_connected)
			leds[0] = CRGB(led_brigthness, 0x00, led_brigthness);
		else if (!setup_done)
			leds[0] = CRGB(led_brigthness, 0x00, 0x00);
		else if (!read_on)
			leds[0] = CRGB(led_brigthness, led_brigthness, 0x00);
		else
			leds[0] = CRGB(0x00, led_brigthness, 0x00);
		FastLED.show();
	}
};
