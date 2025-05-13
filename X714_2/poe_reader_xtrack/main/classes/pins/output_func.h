class output_func
{
public:
	void set_outputs()
	{
		set_gpos();
		set_leds();
	}

	void set_gpos()
	{
		for (int i = 0; i < gpo_qtd; i++)
			gpo[i]
				? pinMode(gpo_pin[i], INPUT_PULLUP)
				: pinMode(gpo_pin[i], OUTPUT);
	}

	void set_leds()
	{
		const int status_time = 3000;
		static unsigned long current_status_time = millis();
		if (status_value == "")
			current_status_time = millis();
		else if (millis() - current_status_time > status_time)
			status_value = "";

		if (!eth_connected)
		{
			digitalWrite(led_ant_pin[1], LOW); // r
			digitalWrite(led_ant_pin[2], LOW); // g
			digitalWrite(led_ant_pin[3], LOW); // b
		}
		else if (!setup_done)
		{
			digitalWrite(led_ant_pin[1], HIGH); // r
			digitalWrite(led_ant_pin[2], LOW);	// g
			digitalWrite(led_ant_pin[3], HIGH); // b
		}
		else if (status_value == "ok")
		{
			digitalWrite(led_ant_pin[1], LOW);	// r
			digitalWrite(led_ant_pin[2], HIGH); // g
			digitalWrite(led_ant_pin[3], LOW);	// b
		}
		else if (status_value == "erro")
		{
			digitalWrite(led_ant_pin[1], HIGH); // r
			digitalWrite(led_ant_pin[2], LOW);	// g
			digitalWrite(led_ant_pin[3], LOW);	// b
		}
		else if (!read_on)
		{
			digitalWrite(led_ant_pin[1], HIGH); // r
			digitalWrite(led_ant_pin[2], HIGH); // g
			digitalWrite(led_ant_pin[3], HIGH); // b
		}
		else
		{
			digitalWrite(led_ant_pin[1], LOW);	// r
			digitalWrite(led_ant_pin[2], LOW);	// g
			digitalWrite(led_ant_pin[3], HIGH); // b
		}
	}
};