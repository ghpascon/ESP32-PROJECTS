class input_func
{
public:
	void check_inputs()
	{
		const int debounce_time = 50;
		static unsigned long current_sensor_in_time = 0;
		static unsigned long current_sensor_out_time = 0;
		static unsigned long current_emg_time = 0;

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
	}
};