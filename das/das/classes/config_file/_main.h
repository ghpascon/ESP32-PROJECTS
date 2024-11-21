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

		else if (parameter.startsWith("door_mode="))
		{
			parameter.replace("door_mode=", "");
			door_mode = parameter.toInt();
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
		
	}

	bool check_save()
	{
		static bool first_time = true;
		static String last_string;
		const String current_string = String(mode)+String(door_mode) + String(retry) + String(speed);

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
		writeFile("door_mode=" + String(door_mode));
		writeFile("retry=" + String(retry));
		writeFile("speed=" + String(speed));
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
