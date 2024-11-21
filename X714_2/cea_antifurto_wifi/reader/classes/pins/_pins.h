#include "vars.h"
#include "input_func.h"
#include "output_func.h"

class PINS : public input_func, public output_func
{
public:
	void setup()
	{
		pinMode(output_on_tags, INPUT_PULLUP);

		pinMode(in_1_pin, INPUT_PULLUP);
		pinMode(in_2_pin, INPUT_PULLUP);
		pinMode(in_3_pin, INPUT_PULLUP);

		pinMode(led_ant_pin[0], OUTPUT);
		pinMode(led_ant_pin[1], OUTPUT);
		pinMode(led_ant_pin[2], OUTPUT);
		pinMode(led_ant_pin[3], OUTPUT);

		pinMode(gpo_pin[0], OUTPUT);
		pinMode(gpo_pin[1], OUTPUT);
		pinMode(gpo_pin[2], OUTPUT);

		pinMode(wifi_led[0], OUTPUT);
		pinMode(wifi_led[1], OUTPUT);
		pinMode(wifi_led[2], OUTPUT);

		pinMode(config_pin, INPUT_PULLUP);

		if (!digitalRead(config_pin))
			config_mode = true;

		Serial.println(config_mode ? "CONFIG MODE" : "OPERATION MODE");
	}
};
