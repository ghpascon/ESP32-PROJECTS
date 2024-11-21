#include "vars.h"

class SERIAL_PORT
{
public:
	void setup()
	{
		Serial.begin(115200);
		Serial2.begin(115200, SERIAL_8N1, rx2_pin, tx2_pin);
		get_data();
	}

	void functions()
	{
		send_data();
		check_serial();
		check_serial2();
	}
	
	void get_data()
	{
		Serial2.println(online ? "#ONLINE" : "#OFFLINE");
		Serial2.println("#api_status:" + api_status);
		Serial2.println("#total_surge:" + total_surge);
		Serial2.println("#device_state:" + String(device_state));
		Serial2.println("#display_message:" + display_message);
	}
private:


	void send_data()
	{
		static bool last_online;
		if (last_online != online)
		{
			last_online = online;
			Serial2.println(online ? "#ONLINE" : "#OFFLINE");
		}

		static String last_api_request;
		if (last_api_request != api_status)
		{
			last_api_request = api_status;
			Serial2.println("#api_status:" + api_status);
		}

		static String last_total_surge;
		if (last_total_surge != total_surge)
		{
			last_total_surge = total_surge;
			Serial2.println("#total_surge:" + total_surge);
		}

		static int last_device_state;
		if (last_device_state != device_state)
		{
			last_device_state = device_state;
			Serial2.println("#device_state:" + String(device_state));
		}

		static String last_display_message;
		if (last_display_message != display_message)
		{
			last_display_message = display_message;
			Serial2.println("#display_message:" + display_message);
		}
	}

	void check_serial()
	{
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

	void check_serial2()
	{
		if (!Serial2.available())
			return;

		String cmd = Serial2.readStringUntil('\n');
		String cmd_original = cmd;
		Serial.println("REC: " + cmd);
		cmd.toLowerCase();
		cmd.replace(" ", "");
		cmd.replace("\r", "");
		cmd.replace("\n", "");

		if (cmd == "#inspec_ok")
		{
			device_state = 0;
		}

		else if (cmd == "#get_data")
		{
			get_data();
		}

		else if (cmd.startsWith("#device_state:"))
		{
			cmd.replace("#device_state:", "");
			device_state = cmd.toInt();
		}
	}
};