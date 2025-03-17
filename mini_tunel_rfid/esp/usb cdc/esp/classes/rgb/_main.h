#include "vars.h"

class LED_RGB
{
public:
	void setup()
	{
		// return;
		FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	}

	void state()
	{
		// return;
		byte led_brigthness = 0x50;
		if (emg)
			leds[0] = CRGB(led_brigthness, 0x00, 0x00);
		else if ((cx_erro || cx_ok) && !motor)
			leds[0] = CRGB(led_brigthness, led_brigthness, led_brigthness);
		else if (cx_erro)
			leds[0] = CRGB(led_brigthness, 0x00, led_brigthness);
		else if (cx_ok)
			leds[0] = CRGB(0x00, led_brigthness, 0x00);
		else if (read_on)
			leds[0] = CRGB(0x00, led_brigthness, led_brigthness);
		else if (motor)
			leds[0] = CRGB(0x00, 0x00, led_brigthness);
		else
			leds[0] = CRGB(led_brigthness, led_brigthness, 0x00);

		FastLED.show();
	}
};
