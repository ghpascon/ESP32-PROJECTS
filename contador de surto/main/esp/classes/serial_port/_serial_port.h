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
		get_data();
		check_serial2();
	}

	void get_data()
	{
		const int send_time = 1000;
		static unsigned long current_send_time = 0;
		if (millis() - current_send_time < send_time)
			return;
		current_send_time = millis();

		Serial2.println(online ? "#ONLINE" : "#OFFLINE");
		Serial2.println("#api_status:" + api_status);
		Serial2.println("#total_surge:" + total_surge);
		Serial2.println("#device_state:" + String(device_state));
		Serial2.println("#display_message:" + display_message);
	}

private:
	void check_serial2()
	{
		if (!Serial2.available())
			return;

		String cmd = Serial2.readStringUntil('\n');
		Serial.println("REC: " + cmd);
		cmd.toLowerCase();
		cmd.replace(" ", "");
		cmd.replace("\r", "");
		cmd.replace("\n", "");

		if (cmd == "#inspec_ok")
		{
			device_state = 0;
		}

		else if (cmd == "#zera_raios")
		{
			total_surge_cnt = 0;
			total_surge = String(total_surge_cnt);
		}
	}
};

