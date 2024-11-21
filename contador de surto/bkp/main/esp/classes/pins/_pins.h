#include "vars.h"
#include "input_func.h"
#include "output_func.h"

class PINS : public input_func, public output_func
{
public:
	void setup()
	{
		pinMode(surge_pin, INPUT_PULLUP);
		pinMode(dps_pin, INPUT_PULLUP);

		pinMode(out_dps, OUTPUT);

		pinMode(setup_pin, INPUT_PULLUP);

		setup_mode = !digitalRead(setup_pin);
		Serial.println(setup_mode ? "Setup Mode" : "Operation mode");

		if (setup_mode)
			api_status = "100";
	}
};
