#include "vars.h"
#include "input_func.h"
#include "output_func.h"

class PINS : public input_func, public output_func
{
public:
	void setup()
	{
		// inputs
		pinMode(sensor_in_pin, INPUT_PULLUP);
		pinMode(sensor_out_pin, INPUT_PULLUP);
		pinMode(emg_pin, INPUT_PULLUP);

		pinMode(p1_close_pin, INPUT_PULLUP);
		pinMode(p1_open_pin, INPUT_PULLUP);
		pinMode(p2_close_pin, INPUT_PULLUP);
		pinMode(p2_open_pin, INPUT_PULLUP);

		// outputs
		pinMode(motor_pin, INPUT_PULLUP);
		pinMode(motor_reverse_pin, INPUT_PULLUP);
		pinMode(speed_1_pin, INPUT_PULLUP);
		pinMode(speed_2_pin, INPUT_PULLUP);
	}
};