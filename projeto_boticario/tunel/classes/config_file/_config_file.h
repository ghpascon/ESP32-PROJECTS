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
		if (parameter.startsWith("speed:"))
		{
			parameter.replace("speed:", "");
			speed = parameter.toInt();
		}

		else if (parameter.startsWith("retry:"))
		{
			parameter.replace("retry:", "");
			retry_cnt = parameter.toInt();
		}
	}

public:
	void save_config()
	{
		clearFile();
		writeFile("speed:" + String(speed));
		writeFile("retry:" + String(retry_cnt));
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
