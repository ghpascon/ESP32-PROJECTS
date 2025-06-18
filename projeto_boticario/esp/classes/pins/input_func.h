class input_func
{
public:
	void check_inputs()
	{
		static unsigned long timers[5];

		input_debounce(sensor_in, !digitalRead(sensor_in_pin), timers[0]);
		input_debounce(sensor_out, !digitalRead(sensor_out_pin), timers[1]);

		input_debounce(emg, digitalRead(emg_pin), timers[2]);

		input_debounce(r700_ok, !digitalRead(r700_ok_pin), timers[3]);
		input_debounce(r700_erro, !digitalRead(r700_erro_pin), timers[4]);
		box_state_r700();
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

	void box_state_r700()
	{
		static bool last_ok = false;
		static bool last_erro = false;
		if (last_ok != r700_ok)
		{
			last_ok = r700_ok;
			cx_ok = !r700_ok ? true : cx_ok;
		}
		if (last_erro != r700_erro)
		{
			last_erro = r700_erro;
			cx_erro = !r700_erro ? true : cx_erro;
		}
	}
};