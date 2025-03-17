#include "vars.h"

class LIGHTNING_SENSOR
{
public:
	void setup()
	{
		// 21-sda
		// 22-scl
		Wire.begin(14, 15);

		if (!lightning.begin())
		{
			Serial.println("Sensor não encontrado. Verifique a conexão!");
			return;
		}
		sensor_found = true;

		lightning.setIndoorOutdoor(0);
		Serial.println("Sensor inicializado com sucesso!");
	}

	void check()
	{
		if (!sensor_found)
			return;
		const int check_time = 1000;
		static unsigned long current_check_time = 0;
		if (millis() - current_check_time < check_time)
			return;
		current_check_time = millis();

		const int noise = 2;	 // Value between 1-7
		const int disturber = 2; // Value between 1-10

		const byte intVal = lightning.readInterruptReg();
		if (intVal == NOISE_INT)
		{
			return;
		}
		else if (intVal == DISTURBER_INT)
		{
			return;
		}
		else if (intVal == LIGHTNING_INT)
		{
			Serial.println("Lightning Strike Detected!");
			lightning_distance = lightning.distanceToStorm();
			if (lightning_distance > 50)
				return;
			Serial.print("Approximately: ");
			Serial.print(lightning_distance);
			Serial.println("km away!");
		}
	}
};
