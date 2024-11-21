class input_func
{
public:
	void check_inputs()
	{
		const int debounce_time = 50;
		static unsigned long current_motor_on_clp_time = 0;
		static unsigned long current_motor_reverse_clp_time = 0;
		static unsigned long enable_time = 0;

		if (!motor_on_clp)
		{
			if (!digitalRead(motor_on_clp_pin))
				current_motor_on_clp_time = millis();
			if (millis() - current_motor_on_clp_time > debounce_time)
			{
				motor_on_clp = true;
				Serial.println("START");
			}
		}
		else
		{
			if (digitalRead(motor_on_clp_pin))
				current_motor_on_clp_time = millis();
			if (millis() - current_motor_on_clp_time > debounce_time)
			{
				motor_on_clp = false;
				Serial.println("STOP");
			}
		}

		// if (!motor_reverse_clp)
		// {
		// 	if (!digitalRead(motor_reverse_clp_pin))
		// 		current_motor_reverse_clp_time = millis();
		// 	if (millis() - current_motor_reverse_clp_time > debounce_time)
		// 	{
		// 		motor_reverse_clp = true;
		// 		Serial.println("VOLTA");
		// 	}
		// }
		// else
		// {
		// 	if (digitalRead(motor_reverse_clp_pin))
		// 		current_motor_reverse_clp_time = millis();
		// 	if (millis() - current_motor_reverse_clp_time > debounce_time)
		// 	{
		// 		motor_reverse_clp = false;
		// 		Serial.println("IDA");
		// 	}
		// }

		// if (!enable)
		// {
		// 	if (!digitalRead(enable_pin))
		// 		enable_time = millis();
		// 	if (millis() - enable_time > debounce_time)
		// 	{
		// 		enable = true;
		// 		Serial.println("ON");
		// 	}
		// }
		// else
		// {
		// 	if (digitalRead(enable_pin))
		// 		enable_time = millis();
		// 	if (millis() - enable_time > debounce_time)
		// 	{
		// 		enable = false;
		// 		Serial.println("OFF");
		// 	}
		// }
	}
};