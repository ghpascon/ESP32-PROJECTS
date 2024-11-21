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

		Serial.println("Escrita concluída: '" + to_write + "' foi adicionado ao arquivo");
	}

	void clearFile()
	{
		File file_config = LittleFS.open(config_file, "w"); // Abre o arquivo em modo de escrita (trunca o arquivo)

		if (!file_config)
		{
			Serial.println("Falha ao abrir o arquivo para limpar");
			return;
		}

		file_config.close();

		Serial.println("Arquivo limpo com sucesso");
	}

	void save_parameter(String parameter)
	{
		if (parameter.startsWith("mode="))
		{
			parameter.replace("mode=", "");
			mode = parameter.toInt();
		}

		else if (parameter.startsWith("retry="))
		{
			parameter.replace("retry=", "");
			retry = parameter.toInt();
		}

		else if (parameter.startsWith("speed="))
		{
			parameter.replace("speed=", "");
			speed = parameter.toInt();
		}

		else if (parameter.startsWith("password="))
		{
			parameter.replace("password=", "");
			password = parameter.toInt();
		}

		else if (parameter.startsWith("ant_cfg_mode_"))
		{
			save_ant_cfg(parameter);
		}
	}

	void save_ant_cfg(String parameter)
	{
		parameter.replace("ant_cfg_mode_", "");

		const byte mode_index = parameter.indexOf("=");
		const byte mode_cfg = parameter.substring(0, mode_index).toInt() - 1;

		parameter = parameter.substring(mode_index + 1);
		const byte sep_index = parameter.indexOf(",");

		const byte power_cfg = parameter.substring(0, sep_index).toInt();
		const byte rssi_cfg = parameter.substring(sep_index + 1).toInt();

		ant_cfg[mode_cfg][0] = power_cfg;
		ant_cfg[mode_cfg][1] = rssi_cfg;
	}

	bool check_save()
	{
		static bool first_time = true;
		static String last_string;
		const String current_string = String(mode) + String(retry) + String(speed) + String(password) + String(ant_cfg[0][0]) + String(ant_cfg[0][1]) + String(ant_cfg[1][0]) + String(ant_cfg[1][1]) + String(ant_cfg[2][0]) + String(ant_cfg[2][1]) + String(ant_cfg[3][0]) + String(ant_cfg[3][1]);

		if (last_string == current_string)
			return false;

		last_string = current_string;

		if (first_time)
		{
			first_time = false;
			return false;
		}
		return true;
	}

public:
	void save_config()
	{
		const int save_time = 10000;
		static unsigned long current_save_time = 0;
		if (millis() - current_save_time < save_time)
			return;

		if (!check_save())
			return;

		current_save_time = millis();

		clearFile();

		writeFile("mode=" + String(mode));
		writeFile("retry=" + String(retry));
		writeFile("speed=" + String(speed));
		writeFile("password=" + String(password));

		byte current_mode = 0;
		writeFile("ant_cfg_mode_1=" + String(ant_cfg[current_mode][0]) + "," + String(ant_cfg[current_mode][1]));
		current_mode = 1;
		writeFile("ant_cfg_mode_2=" + String(ant_cfg[current_mode][0]) + "," + String(ant_cfg[current_mode][1]));
		current_mode = 2;
		writeFile("ant_cfg_mode_3=" + String(ant_cfg[current_mode][0]) + "," + String(ant_cfg[current_mode][1]));
		current_mode = 3;
		writeFile("ant_cfg_mode_4=" + String(ant_cfg[current_mode][0]) + "," + String(ant_cfg[current_mode][1]));
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
			line.replace("\n", "");
			line.replace("\r", "");
			line.replace(" ", "");
			Serial.println(line);
			save_parameter(line);
		}

		file_config.close();
	}
};
