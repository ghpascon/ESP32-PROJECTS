#include "vars.h"
#include "input_func.h"
#include "output_func.h"

class PINS : public input_func, public output_func
{
public:
	void setup()
	{
		// pinMode(in_1_pin, INPUT_PULLUP);
		// pinMode(in_2_pin, INPUT_PULLUP);
		// pinMode(in_3_pin, INPUT_PULLUP);

		pinMode(led_ant_pin[0], OUTPUT);
		pinMode(led_ant_pin[1], INPUT_PULLUP);
		// pinMode(led_ant_pin[2], INPUT_PULLUP);
		// pinMode(led_ant_pin[3], INPUT_PULLUP);

		// pinMode(gpo_pin[0], OUTPUT);
		// pinMode(gpo_pin[1], OUTPUT);
		// pinMode(gpo_pin[2], OUTPUT);
	}
};
