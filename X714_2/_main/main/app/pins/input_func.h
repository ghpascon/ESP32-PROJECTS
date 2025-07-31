class input_func
{
public:
	void check_inputs()
	{

		static unsigned long current_in_1_time = 0;
		input_debounce(in_1, !digitalRead(in_1_pin), current_in_1_time);

		static unsigned long current_in_2_time = 0;
		input_debounce(in_2, !digitalRead(in_2_pin), current_in_2_time);

		static unsigned long current_in_3_time = 0;
		input_debounce(in_3, !digitalRead(in_3_pin), current_in_3_time);

		gpi_state();
	}

	void input_debounce(bool &state, bool current_state, unsigned long &last_time, int debounce_time = 50)
	{
		if (current_state != state)
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
	}

	void gpi_state()
	{
		gpi_start ? gpi_read() : gpi_serial();
	}

	void gpi_read()
	{
		static bool read_on_aux = false;
		static bool start_in_2 = false;

		if (!start_in_2)
			read_on_aux = in_1;

		if (in_2)
		{
			read_on_aux = true;
			start_in_2 = true;
		}

		if (in_3)
		{
			read_on_aux = false;
			start_in_2 = false;
		}

		gpi_set_read_on(read_on_aux);
	}

	void gpi_set_read_on(bool read_on_aux)
	{
		static unsigned long current_stop_read_timeout = -gpi_stop_delay;
		if (read_on_aux)
			current_stop_read_timeout = millis();
		read_on = (millis() - current_stop_read_timeout < gpi_stop_delay + 20);
	}

	void gpi_serial()
	{
		static bool last_in_1 = false;
		static bool last_in_2 = false;
		static bool last_in_3 = false;

		if (last_in_1 != in_1)
		{
			last_in_1 = in_1;
			myserial.write("#IN_1:" + String(in_1 ? "ON" : "OFF"));
		}

		if (last_in_2 != in_2)
		{
			last_in_2 = in_2;
			myserial.write("#IN_2:" + String(in_2 ? "ON" : "OFF"));
		}

		if (last_in_3 != in_3)
		{
			last_in_3 = in_3;
			myserial.write("#IN_3:" + String(in_3 ? "ON" : "OFF"));
		}
	}
};