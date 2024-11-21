#include "vars.h"
#include "input_func.h"
#include "output_func.h"

class PINS : public input_func, public output_func
{
public:
	void setup()
	{
		// inputs
		pinMode(motor_on_clp_pin, INPUT);
		// pinMode(motor_reverse_clp_pin, INPUT);
		pinMode(enable_pin, INPUT);

		// outputs
		pinMode(motor_pin, OUTPUT);
		// pinMode(motor_reverse_pin, OUTPUT);
		pinMode(enable_driver, OUTPUT);
	}
};