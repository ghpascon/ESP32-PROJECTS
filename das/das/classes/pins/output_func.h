class output_func
{
public:
	void set_outputs()
	{
		motor ? pinMode(motor_pin, INPUT_PULLUP) : pinMode(motor_pin, OUTPUT);
		motor_reverse ? pinMode(motor_reverse_pin, INPUT_PULLUP) : pinMode(motor_reverse_pin, OUTPUT);
		if (speed == 1)
		{
			pinMode(speed_1_pin, OUTPUT);
			pinMode(speed_2_pin, OUTPUT);
		}
		else if (speed == 2)
		{
			pinMode(speed_1_pin, INPUT_PULLUP);
			pinMode(speed_2_pin, OUTPUT);
		}
		else if (speed == 3)
		{
			pinMode(speed_1_pin, OUTPUT);
			pinMode(speed_2_pin, INPUT_PULLUP);
		}
		else if (speed == 4)
		{
			pinMode(speed_1_pin, INPUT_PULLUP);
			pinMode(speed_2_pin, INPUT_PULLUP);
		}
		else
			speed = 1;

		send_read_state();
	}

	void send_read_state()
	{
		static bool last_read=false;
		if(last_read==read_on)
			return;
		last_read = read_on;
		Serial.println("#READ:" + String(read_on ? "ON" : "OFF"));
		Serial1.println("#READ:" + String(read_on ? "ON" : "OFF"));
	}
};