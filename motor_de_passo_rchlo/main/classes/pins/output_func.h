class output_func
{
public:
	void set_outputs()
	{
		const int enable_time = 10000;
		static unsigned long current_enable_time = 0;
		if (motor_on_clp)
		{
			step_motor_on();
			current_enable_time = millis();
		}
		// motor_reverse_clp ? pinMode(motor_reverse_pin, INPUT_PULLUP) : pinMode(motor_reverse_pin, OUTPUT);

		 digitalWrite(enable_driver, (millis() - current_enable_time > enable_time) ? HIGH : LOW);
	}

private:
	void step_motor_on()
	{
		const int motor_time = 40;
		static unsigned long current_motor_time = 0;

		if (current_motor_time > micros())
			current_motor_time = 0;

		if (micros() - current_motor_time < motor_time)
			return;
		current_motor_time = micros();

		static bool last_state = false;
		last_state = !last_state;
		// last_state ? pinMode(motor_pin, INPUT_PULLUP) : pinMode(motor_pin, OUTPUT);
		digitalWrite(motor_pin, last_state ? HIGH : LOW);
	}
};