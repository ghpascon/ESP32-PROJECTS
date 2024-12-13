class output_func
{
public:
	void set_outputs()
	{
		motor ? pinMode(motor_pin, OUTPUT) : pinMode(motor_pin, INPUT_PULLUP);
		motor_reverse ? pinMode(motor_reverse_pin, OUTPUT) : pinMode(motor_reverse_pin, INPUT_PULLUP);
		if (speed == 1)
		{
			pinMode(speed_1_pin, INPUT_PULLUP);
			pinMode(speed_2_pin, INPUT_PULLUP);
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
			pinMode(speed_1_pin, OUTPUT);
			pinMode(speed_2_pin, OUTPUT);
		}
		else
			speed = 1;

		send_read_state();
		set_status_str();
	}

private:
	void send_read_state()
	{
		static bool last_read = false;
		if (last_read == read_on)
			return;
		last_read = read_on;
		Serial.println("#READ:" + String(read_on ? "ON" : "OFF"));
		Serial1.println("#READ:" + String(read_on ? "ON" : "OFF"));
	}

	void set_status_str()
	{
		String current_status_msg = "";
		current_status_msg += "MOTOR: " + String(motor ? (motor_reverse ? "REVERSE" : "ON") : "OFF");
		current_status_msg += "\n";
		current_status_msg += "STATUS: " + String(cx_ok ? "CX: OK" : (cx_erro ? "CX: ERRO" : "---"));
		current_status_msg += "\n";
		current_status_msg += "READING: " + String(read_on ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "BOX_INSIDE: " + String(box_inside ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "\n";
		if (client != 1)
		{
			current_status_msg += "PERFIL: " + String(mode - 2);
			current_status_msg += "\n";
			current_status_msg += "MODE: " + String(door_mode);
			current_status_msg += "\n";
		}
		current_status_msg += "SPEED: " + String(speed);
		current_status_msg += "\n";
		current_status_msg += "RETRY: " + String(retry);
		current_status_msg += "\n";
		current_status_msg += "SENSOR_IN: " + String(sensor_in ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "SENSOR_OUT: " + String(sensor_out ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "EMG: " + String(emg ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "P1_CLOSE: " + String(p1_close ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "P1_OPEN: " + String(p1_open ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "P2_CLOSE: " + String(p2_close ? "ON" : "OFF");
		current_status_msg += "\n";
		current_status_msg += "P2_OPEN: " + String(p2_open ? "ON" : "OFF");
		status_msg = current_status_msg;
	}
};