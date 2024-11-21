#include "vars.h"

class SERIAL_PORT
{
public:
	void setup()
	{
		Serial.begin(115200, SERIAL_8N1, rx2_pin, tx2_pin);
		// Serial.begin(115200);
		Serial.println("#GET_DATA");
	}

	void functions()
	{
		send_inspec();

		if (!Serial.available())
			return;

		String cmd = Serial.readStringUntil('\n');
		String cmd_original = cmd;
		cmd.toLowerCase();
		cmd.replace(" ", "");
		cmd.replace("\r", "");
		cmd.replace("\n", "");

		if (cmd == "#online")
		{
			online = true;
		}
		else if (cmd == "#offline")
		{
			online = false;
		}

		else if (cmd.startsWith("#api_status:"))
		{
			cmd.replace("#api_status:", "");
			api_status = cmd;
		}

		else if (cmd.startsWith("#total_surge:"))
		{
			cmd.replace("#total_surge:", "");
			total_surge = cmd;
		}

		else if (cmd.startsWith("#device_state:"))
		{
			cmd.replace("#device_state:", "");
			device_state = cmd.toInt();
		}

		else if (cmd.startsWith("#display_message:"))
		{
			cmd_original.replace("#display_message:", "");
			display_message = cmd_original;
		}

		else
		{
			Serial.println("#E_INVALID_CMD");
		}
	}

private:
	void send_inspec()
	{
		const int password_time = 500;
		static unsigned long current_password_time = 0;
		static int times=0;
		if (millis() - current_password_time < password_time)
			return;
		current_password_time = millis();

		if (password_ok)
		{
			Serial.println("#inspec_ok");
			times++;
		}
		else
			times = 0;

		if (times > 5)
			password_ok = false;
	}
};