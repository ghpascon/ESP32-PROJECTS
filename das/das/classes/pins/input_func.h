class input_func
{
public:
	void check_inputs()
	{

		static unsigned long current_sensor_in_time = 0;
		sensor_in = debounce(sensor_in, digitalRead(sensor_in_pin), current_sensor_in_time);
		static unsigned long current_sensor_out_time = 0;
		sensor_out = debounce(sensor_out, digitalRead(sensor_out_pin), current_sensor_out_time);

		static unsigned long current_emg_time = 0;
		emg = debounce(emg, !digitalRead(emg_pin), current_emg_time);

		static unsigned long current_p1_close_time = 0;
		p1_close = debounce(p1_close, digitalRead(p1_close_pin), current_p1_close_time);
		static unsigned long current_p1_open_time = 0;
		p1_open = debounce(p1_open, digitalRead(p1_open_pin), current_p1_open_time);
		static unsigned long current_p2_close_time = 0;
		p2_close = debounce(p2_close, digitalRead(p2_close_pin), current_p2_close_time);
		static unsigned long current_p2_open_time = 0;
		p2_open = debounce(p2_open, digitalRead(p2_open_pin), current_p2_open_time);
	}

private:
	bool debounce(bool state, bool current_read, unsigned long &last_time, int debounce_time = 50, )
	{
		if (current_read == state)
		{
			if (millis() - last_time > debounce_time)
			{
				state = !state;
			}
		}
		else
		{
			last_time = millis();
		}

		return state;
	}
};