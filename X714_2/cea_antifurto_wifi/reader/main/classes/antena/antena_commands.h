#include "vars.h"

class ANTENA_COMMANDS
{
public:
	void set_antena(int num, bool active, byte power, byte rssi)
	{
		if (num < 1 || num > ant_qtd)
			return;

		antena[num - 1].active = active;
		antena[num - 1].power = power;
		antena[num - 1].rssi = rssi;
	}

	void set_power_all(byte set_power)
	{
		set_power = constrain(set_power, min_power, max_power);

		for (int i = 0; i < ant_qtd; i++)
		{
			antena[i].power = set_power;
		}

		Serial.print(" - " + String(set_power, DEC));
	}
};