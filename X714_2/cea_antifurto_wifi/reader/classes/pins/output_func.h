class output_func
{
public:
	void set_outputs()
	{
		set_gpos();
		ant_leds();
		led_wifi();
	}

	void set_gpos()
	{
		for (int i = 0; i < gpo_qtd; i++)
			gpo[i]
				? pinMode(gpo_pin[i], INPUT_PULLUP)
				: pinMode(gpo_pin[i], OUTPUT);
	}

	void ant_led_turn_on(int ant_number)
	{
		if (ant_number < 1 || ant_number > ant_qtd)
			return;

		current_led_ant_time[0] = millis();
	}

	void ant_leds()
	{
		if (millis() - current_led_ant_time[0] < led_ant_time)
		{
			digitalWrite(led_ant_pin[0], HIGH);
			pinMode(output_on_tags, OUTPUT);
		}
		else
		{
			digitalWrite(led_ant_pin[0], LOW);
			pinMode(output_on_tags, INPUT_PULLUP);
		}
	}

	void led_wifi()
	{
		if (config_mode)
		{
			digitalWrite(wifi_led[0], LOW);
			digitalWrite(wifi_led[1], LOW);
			digitalWrite(wifi_led[2], HIGH);
			return;
		}

		if (!setup_done)
		{
			digitalWrite(wifi_led[0], HIGH);
			digitalWrite(wifi_led[1], LOW);
			digitalWrite(wifi_led[2], LOW);
		}
		else if (!connected)
		{
			static bool flag;
			flag = !flag;
			if (flag)
			{
				digitalWrite(wifi_led[0], HIGH);
				digitalWrite(wifi_led[1], LOW);
				digitalWrite(wifi_led[2], LOW);
			}
			else
			{
				digitalWrite(wifi_led[0], LOW);
				digitalWrite(wifi_led[1], HIGH);
				digitalWrite(wifi_led[2], LOW);
			}
		}
		else
		{
			digitalWrite(wifi_led[0], LOW);
			digitalWrite(wifi_led[1], HIGH);
			digitalWrite(wifi_led[2], LOW);
		}
	}
};