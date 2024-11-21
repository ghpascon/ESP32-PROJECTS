class output_func
{
public:
	void set_outputs()
	{
		set_gpos();
		ant_leds();
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
};