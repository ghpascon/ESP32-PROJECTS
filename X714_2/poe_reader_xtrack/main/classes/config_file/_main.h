#include "vars.h"

class CONFIG_FILE
{
private:
	void writeFile(String to_write)
	{
		File file_config = LittleFS.open(config_file, "a");
		if (!file_config)
		{
			Serial.println("#E_SAVE_CONFIG");
			return;
		}

		file_config.print("\n" + to_write);
		file_config.close();

		if (debug_mode)
			Serial.println("Escrita concluída: '" + to_write + "' foi adicionado ao arquivo");
	}

	void clearFile()
	{
		File file_config = LittleFS.open(config_file, "w"); // Abre o arquivo em modo de escrita (trunca o arquivo)

		if (!file_config)
		{
			if (debug_mode)
				Serial.println("Falha ao abrir o arquivo para limpar");
			return;
		}

		file_config.close();

		if (debug_mode)
			Serial.println("Arquivo limpo com sucesso");
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
			const String current_active = parameter.substring(0, start_antena_data);
			parameter = parameter.substring(start_antena_data + 1);

			start_antena_data = parameter.indexOf(antena_data_prefix);
			byte current_power = parameter.substring(0, start_antena_data).toInt();
			parameter = parameter.substring(start_antena_data + 1);

			byte current_rssi = parameter.toInt();

			if (current_power > max_power)
				current_power = max_power;
			if (current_power < min_power)
				current_power = min_power;
			if (current_rssi < min_rssi)
				current_rssi = min_rssi;
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

		else if (parameter.startsWith("url:"))
		{
			parameter.replace("url:", "");
			url = parameter;
		}
		else if (parameter.startsWith("esp_name:"))
		{
			parameter.replace("esp_name:", "");
			esp_name = parameter;
		}
		else if (parameter.startsWith("buzzer_vol:"))
		{
			parameter.replace("buzzer_vol:", "");
			buzzer_vol = parameter.toInt();
		}

		else if (parameter.startsWith("buzzer_on:"))
		{
			parameter.replace("buzzer_on:", "");
			buzzer_on = (parameter == "on");
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
		writeFile("url:" + String(url));
		writeFile("esp_name:" + String(esp_name));
		writeFile("buzzer_vol:" + String(buzzer_vol));
		writeFile("buzzer_on:" + String(buzzer_on ? "on" : "off"));
	}

	void get_config()
	{
		File file_config = LittleFS.open(config_file, "r");

		if (!file_config)
		{
			Serial.println("Falha ao abrir o arquivo para leitura");
			return;
		}

		Serial.println("Conteúdo do arquivo:");
		while (file_config.available())
		{
			String line = file_config.readStringUntil('\n');
			line.toLowerCase();
			line.replace(" ", "");
			line.replace("\r", "");
			line.replace("\n", "");
			Serial.println(line);
			save_parameter(line);
		}

		file_config.close();
	}
};
