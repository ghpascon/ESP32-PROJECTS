class output_func
{
public:
	void set_outputs()
	{
		set_gpos();
		ant_leds();
		connection_led();
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

		current_led_ant_time[ant_number - 1] = millis();
	}
	void ant_leds()
	{
		for (int i = 0; i < ant_qtd; i++)
			(millis() - current_led_ant_time[i] < led_ant_time)
				? digitalWrite(led_ant_pin[i], HIGH)
				: digitalWrite(led_ant_pin[i], LOW);
	}

	void connection_led()
	{
		if (!setup_done)
		{
			digitalWrite(led_vermelho, HIGH);
			digitalWrite(led_verde, LOW);
			digitalWrite(led_azul, LOW);
		}
		else if (!eth_connected)
		{
			static bool flag = false;
			flag = !flag;
			if (flag)
			{
				digitalWrite(led_vermelho, HIGH);
				digitalWrite(led_verde, LOW);
				digitalWrite(led_azul, LOW);
			}
			else
			{
				digitalWrite(led_vermelho, LOW);
				digitalWrite(led_verde, HIGH);
				digitalWrite(led_azul, LOW);
			}
		}
		else if (read_on)
		{
			digitalWrite(led_vermelho, LOW);
			digitalWrite(led_verde, HIGH);
			digitalWrite(led_azul, LOW);
		}
		else
		{
			digitalWrite(led_vermelho, LOW);
			digitalWrite(led_verde, LOW);
			digitalWrite(led_azul, HIGH);
		}
	}
};