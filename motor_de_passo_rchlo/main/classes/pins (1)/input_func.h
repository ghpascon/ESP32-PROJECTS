class input_func
{
public:
	void check_inputs()
	{
		const int surge_time = 300000;
		static unsigned long current_surge_time = 0;

		const int debounce_time = 100;
		static unsigned long current_dps_time = 0;

		if (!surge)
		{
			if (!digitalRead(surge_pin))
				surge = true;
		}
		else
		{
			if (!digitalRead(surge_pin))
				current_surge_time = millis();
			if (millis() - current_surge_time > surge_time)
				surge = false;
		}

		if (!dps)
		{
			if (digitalRead(dps_pin))
				current_dps_time = millis();
			if (millis() - current_dps_time > debounce_time)
				dps = true;
		}
		else
		{
			if (!digitalRead(dps_pin))
				current_dps_time = millis();
			if (millis() - current_dps_time > debounce_time)
				dps = false;
		}

		set_state_surge();
		set_state_dps();
		reset_setup();
	}
};