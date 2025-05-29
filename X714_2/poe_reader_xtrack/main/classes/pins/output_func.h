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

	void set_buzzer()
	{
		const int time = 2000;

		if (millis() < time)
			return;

		if (millis() - buzzer_time < time && buzzer_on)
		{
			pinMode(led_ant_pin[3], OUTPUT);
			analogWrite(led_ant_pin[3], 255-buzzer_vol);
		}
		else
			pinMode(led_ant_pin[3], INPUT_PULLUP);
	}

	void set_leds()
	{
		set_buzzer();
		const int status_time = 3000;
		static unsigned long current_status_time = millis();
		if (status_value == "")
			current_status_time = millis();
		else if (millis() - current_status_time > status_time)
			status_value = "";
		if (!eth_connected)
		{
			digitalWrite(led_ant_pin[0], LOW); // r
			digitalWrite(led_ant_pin[1], LOW); // g
			digitalWrite(led_ant_pin[2], LOW); // b
		}
		else if (!setup_done)
		{
			digitalWrite(led_ant_pin[0], HIGH); // r
			digitalWrite(led_ant_pin[1], LOW);	// g
			digitalWrite(led_ant_pin[2], HIGH); // b
		}
		else if (status_value == "ok")
		{
			digitalWrite(led_ant_pin[0], LOW);	// r
			digitalWrite(led_ant_pin[1], HIGH); // g
			digitalWrite(led_ant_pin[2], LOW);	// b
		}
		else if (status_value == "erro")
		{
			digitalWrite(led_ant_pin[0], HIGH); // r
			digitalWrite(led_ant_pin[1], LOW);	// g
			digitalWrite(led_ant_pin[2], LOW);	// b
		}
		else if (!read_on)
		{
			digitalWrite(led_ant_pin[0], HIGH); // r
			digitalWrite(led_ant_pin[1], HIGH); // g
			digitalWrite(led_ant_pin[2], HIGH); // b
		}
		else
		{
			digitalWrite(led_ant_pin[0], LOW);	// r
			digitalWrite(led_ant_pin[1], LOW);	// g
			digitalWrite(led_ant_pin[2], HIGH); // b
		}
	}
};