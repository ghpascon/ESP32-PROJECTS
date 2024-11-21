class input_func
{
public:
	void check_inputs()
	{
		const int debounce_time = 50;
		static unsigned long current_sensor_in_time = 0;
		static unsigned long current_sensor_out_time = 0;
		static unsigned long current_emg_time = 0;
		static unsigned long current_p1_close_time = 0;
		static unsigned long current_p1_open_time = 0;
		static unsigned long current_p2_close_time = 0;
		static unsigned long current_p2_open_time = 0;

		// in_out
		if (!sensor_in)
		{
			if (digitalRead(sensor_in_pin))
				current_sensor_in_time = millis();
			if (millis() - current_sensor_in_time > debounce_time)
				sensor_in = true;
		}
		else
		{
			if (!digitalRead(sensor_in_pin))
				current_sensor_in_time = millis();
			if (millis() - current_sensor_in_time > debounce_time)
				sensor_in = false;
		}

		if (!sensor_out)
		{
			if (digitalRead(sensor_out_pin))
				current_sensor_out_time = millis();
			if (millis() - current_sensor_out_time > debounce_time)
				sensor_out = true;
		}
		else
		{
			if (!digitalRead(sensor_out_pin))
				current_sensor_out_time = millis();
			if (millis() - current_sensor_out_time > debounce_time)
				sensor_out = false;
		}

		// emg
		if (!emg)
		{
			if (!digitalRead(emg_pin))
				current_emg_time = millis();
			if (millis() - current_emg_time > debounce_time)
				emg = true;
		}
		else
		{
			if (digitalRead(emg_pin))
				current_emg_time = millis();
			if (millis() - current_emg_time > debounce_time)
				emg = false;
		}

		//doors
		if (!p1_close)
		{
			if (digitalRead(p1_close_pin))
				current_p1_close_time = millis();
			if (millis() - current_p1_close_time > debounce_time)
				p1_close = true;
		}
		else
		{
			if (!digitalRead(p1_close_pin))
				current_p1_close_time = millis();
			if (millis() - current_p1_close_time > debounce_time)
				p1_close = false;
		}

		if (!p1_open)
		{
			if (digitalRead(p1_open_pin))
				current_p1_open_time = millis();
			if (millis() - current_p1_open_time > debounce_time)
				p1_open = true;
		}
		else
		{
			if (!digitalRead(p1_open_pin))
				current_p1_open_time = millis();
			if (millis() - current_p1_open_time > debounce_time)
				p1_open = false;
		}

		if (!p2_close)
		{
			if (digitalRead(p2_close_pin))
				current_p2_close_time = millis();
			if (millis() - current_p2_close_time > debounce_time)
				p2_close = true;
		}
		else
		{
			if (!digitalRead(p2_close_pin))
				current_p2_close_time = millis();
			if (millis() - current_p2_close_time > debounce_time)
				p2_close = false;
		}

		if (!p2_open)
		{
			if (digitalRead(p2_open_pin))
				current_p2_open_time = millis();
			if (millis() - current_p2_open_time > debounce_time)
				p2_open = true;
		}
		else
		{
			if (!digitalRead(p2_open_pin))
				current_p2_open_time = millis();
			if (millis() - current_p2_open_time > debounce_time)
				p2_open = false;
		}
	}
};