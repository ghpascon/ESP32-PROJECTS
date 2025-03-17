class input_func
{
public:
	void check_inputs()
	{
		static unsigned long timers[7];

		input_debounce(sensor_in, !digitalRead(sensor_in_pin), timers[0]);
		input_debounce(sensor_out, !digitalRead(sensor_out_pin), timers[1]);

		input_debounce(emg, digitalRead(emg_pin), timers[2]);

		input_debounce(p1_close, !digitalRead(p1_close_pin), timers[3]);
		input_debounce(p1_open, !digitalRead(p1_open_pin), timers[4]);
		input_debounce(p2_close, !digitalRead(p2_close_pin), timers[5]);
		input_debounce(p2_open, !digitalRead(p2_open_pin), timers[6]);
	}

private:
	bool input_debounce(bool &state, bool current_read, unsigned long &last_time, int debounce_time = 50)
	{
		if (current_read != state)
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