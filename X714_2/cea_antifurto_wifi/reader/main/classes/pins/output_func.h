class output_func
{
public:
	void set_outputs()
	{
		// set_gpos();
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
		current_led_ant_time[0] = millis();
	}
	void ant_leds()
	{
		if (millis() < 1000)
			return;
		(millis() - current_led_ant_time[0] < led_ant_time) ? digitalWrite(led_ant_pin[0], HIGH) : digitalWrite(led_ant_pin[0], LOW);
		(millis() - current_led_ant_time[0] < led_ant_time) ? pinMode(led_ant_pin[1], OUTPUT) : pinMode(led_ant_pin[1], INPUT_PULLUP);
	}
};