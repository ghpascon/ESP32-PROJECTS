class input_func
{
public:
	void check_inputs()
	{
		const int surge_time = 10000;
		static unsigned long current_surge_time = 0;

		const int debounce_time = 1000;
		static unsigned long current_dps_time = 0;

		if (!surge)
		{
			if (!digitalRead(surge_pin))
			{
				surge = true;
				current_surge_time = millis();
			}
		}
		else
		{
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

	void set_state_surge()
	{
		static bool last_surge_state = false;
		if (last_surge_state == surge)
			return;
		last_surge_state = surge;

		if (surge)
		{
			device_state = 1;
			total_surge_cnt++;
			total_surge = String(total_surge_cnt);
		}
	}

	void set_state_dps()
	{
		static bool last_dps_state = false;

		if (last_dps_state == dps)
			return;

		last_dps_state = dps;
		device_state = dps ? 2 : 1;

		if (dps)
		{
			total_surge_cnt++;
			total_surge = String(total_surge_cnt);
		}
	}

	void reset_setup()
	{
		const int reset_time = 3000;
		static unsigned long current_reset_time = 0;

		if (digitalRead(setup_pin))
			current_reset_time = millis();

		if (millis() - current_reset_time > reset_time)
			ESP.restart();
	}
};