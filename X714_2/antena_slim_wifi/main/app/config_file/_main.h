#include "vars.h"

class CONFIG_FILE
{
private:
	void writeFile(String to_write)
	{
		File file_config = LittleFS.open(config_file, "a");
		if (!file_config)
		{
			return;
		}

		file_config.print("\n" + to_write);
		file_config.close();
	}

	void clearFile()
	{
		File file_config = LittleFS.open(config_file, "w"); // Abre o arquivo em modo de escrita (trunca o arquivo)

		if (!file_config)
		{
			return;
		}

		file_config.close();
	}

	void save_parameter(String parameter)
	{
		if (parameter.startsWith("antena:"))
		{
			const String antena_data_prefix = ",";
			int start_antena_data;

			parameter.replace("antena:", "");

			start_antena_data = parameter.indexOf(antena_data_prefix);
			const int current_ant = parameter.substring(0, start_antena_data).toInt();
			parameter = parameter.substring(start_antena_data + 1);

			start_antena_data = parameter.indexOf(antena_data_prefix);
			String current_active = parameter.substring(0, start_antena_data);
			parameter = parameter.substring(start_antena_data + 1);

			start_antena_data = parameter.indexOf(antena_data_prefix);
			byte current_power = parameter.substring(0, start_antena_data).toInt();
			parameter = parameter.substring(start_antena_data + 1);

			byte current_rssi = parameter.toInt();

			current_power = constrain(current_power, min_power, max_power);
			current_rssi = max(current_rssi, min_rssi);

			if (one_ant)
				current_active = "on";

			antena_commands.set_antena(current_ant, (current_active == "on" ? true : false), current_power, current_rssi);
		}

		else if (parameter.startsWith("session:"))
		{
			parameter.replace("session:", "");
			session = parameter.toInt();
			if (session > max_session)
				session = 0x00;
		}

		else if (parameter.startsWith("start_reading:"))
		{
			parameter.replace("start_reading:", "");
			start_reading = (parameter == "on");
			read_on = start_reading;
		}

		else if (parameter.startsWith("gpi_start:"))
		{
			parameter.replace("gpi_start:", "");
			gpi_start = (parameter == "on");
		}

		else if (parameter.startsWith("gpi_stop_delay:"))
		{
			parameter.replace("gpi_stop_delay:", "");
			gpi_stop_delay = parameter.toInt();
		}

		else if (parameter.startsWith("ignore_read:"))
		{
			parameter.replace("ignore_read:", "");
			ignore_read = (parameter == "on");
		}

		else if (parameter.startsWith("always_send:"))
		{
			parameter.replace("always_send:", "");
			always_send = (parameter == "on");
		}

		else if (parameter.startsWith("simple_send:"))
		{
			parameter.replace("simple_send:", "");
			simple_send = (parameter == "on");
		}

		else if (parameter.startsWith("hotspot_on:"))
		{
			parameter.replace("hotspot_on:", "");
			hotspot_on = (parameter == "on");
		}

		else if (parameter.startsWith("keyboard:"))
		{
			parameter.replace("keyboard:", "");
			keyboard = (parameter == "on");
		}

		else if (parameter.startsWith("wifi_ssid:"))
		{
			parameter.replace("wifi_ssid:", "");
			wifi_ssid = parameter;
		}
		else if (parameter.startsWith("wifi_password:"))
		{
			parameter.replace("wifi_password:", "");
			wifi_password = parameter;
		}
		else if (parameter.startsWith("wifi_url:"))
		{
			parameter.replace("wifi_url:", "");
			wifi_url = parameter;
		}
		else if (parameter.startsWith("wifi_name:"))
		{
			parameter.replace("wifi_name:", "");
			wifi_name = parameter;
		}
	}

public:
	void save_config()
	{
		clearFile();
		for (int i = 0; i < ant_qtd; i++)
		{
			writeFile("antena:" + String(i + 1) + "," + String(antena[i].active ? "on" : "off") + "," + String(antena[i].power) + "," + String(antena[i].rssi));
		}
		writeFile("session:" + String(session, DEC));
		writeFile("start_reading:" + String(start_reading ? "on" : "off"));
		writeFile("gpi_start:" + String(gpi_start ? "on" : "off"));
		writeFile("gpi_stop_delay:" + String(gpi_stop_delay));
		writeFile("ignore_read:" + String(ignore_read ? "on" : "off"));
		writeFile("always_send:" + String(always_send ? "on" : "off"));
		writeFile("simple_send:" + String(simple_send ? "on" : "off"));
		writeFile("hotspot_on:" + String(hotspot_on ? "on" : "off"));
		writeFile("keyboard:" + String(keyboard ? "on" : "off"));
		writeFile("wifi_ssid:" + String(wifi_ssid));
		writeFile("wifi_password:" + String(wifi_password));
		writeFile("wifi_url:" + String(wifi_url));
		writeFile("wifi_name:" + String(wifi_name));
	}

	void get_config()
	{
		File file_config = LittleFS.open(config_file, "r");

		if (!file_config)
		{
			return;
		}

		while (file_config.available())
		{
			String line = file_config.readStringUntil('\n');
			line.replace("\r", "");
			line.replace("\n", "");
			save_parameter(line);
		}

		file_config.close();
	}
};
