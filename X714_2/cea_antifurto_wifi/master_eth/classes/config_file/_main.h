#include "vars.h"
#include "get_cmd.h"

class CONFIG_FILE : public get_cmd
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
		if (parameter.startsWith("url:"))
		{
			parameter.replace("url:", "");
			url = parameter;
		}

		else if (parameter.startsWith("ip:"))
		{
			parameter.replace("ip:", "");
			get_ip(parameter, 0);
		}
		else if (parameter.startsWith("gateway:"))
		{
			parameter.replace("gateway:", "");
			get_ip(parameter, 1);
		}
		else if (parameter.startsWith("subnet:"))
		{
			parameter.replace("subnet:", "");
			get_ip(parameter, 2);
		}
		else if (parameter.startsWith("dns:"))
		{
			parameter.replace("dns:", "");
			get_ip(parameter, 3);
		}

		else
		{
			Serial.println("#E_INVALID_CMD");
		}
	}

public:
	void save_config()
	{
		clearFile();
		writeFile("ip:" + String(ip_config[0][0]) + "." + String(ip_config[1][0]) + "." + String(ip_config[2][0]) + "." + String(ip_config[3][0]));
		writeFile("gateway:" + String(ip_config[0][1]) + "." + String(ip_config[1][1]) + "." + String(ip_config[2][1]) + "." + String(ip_config[3][1]));
		writeFile("subnet:" + String(ip_config[0][2]) + "." + String(ip_config[1][2]) + "." + String(ip_config[2][2]) + "." + String(ip_config[3][2]));
		writeFile("dns:" + String(ip_config[0][3]) + "." + String(ip_config[1][3]) + "." + String(ip_config[2][3]) + "." + String(ip_config[3][2]));
		writeFile("url:" + url);
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
		show_config();
	}
};
