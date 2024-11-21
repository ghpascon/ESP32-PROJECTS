#include "vars.h"

class RESET
{
public:
	void check()
	{
		const int motor_timeout = 300000;
		static unsigned long current_motor_timeout = 0;
		if (motor_on_clp)
			current_motor_timeout = millis();

		if (millis() - current_motor_timeout < motor_timeout)
			return;

		ESP.restart();
	}
};