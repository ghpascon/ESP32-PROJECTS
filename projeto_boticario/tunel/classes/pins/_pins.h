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

		// outputs
		pinMode(motor_pin, OUTPUT);
		pinMode(motor_reverse_pin, OUTPUT);
		pinMode(speed_1_pin, OUTPUT);
		pinMode(speed_2_pin, OUTPUT);
	}
};