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
		if (parameter.startsWith("total_surge_cnt:"))
		{
			parameter.replace("total_surge_cnt:", "");
			total_surge_cnt = parameter.toInt();
			total_surge = String(total_surge_cnt);
		}

		else if (parameter.startsWith("device_state:"))
		{
			parameter.replace("device_state:", "");
			device_state = parameter.toInt();
		}

		else if (parameter.startsWith("nome:"))
		{
			parameter.replace("nome:", "");
			nome = parameter;
		}
		else if (parameter.startsWith("rede:"))
		{
			parameter.replace("rede:", "");
			rede = parameter;
		}
		else if (parameter.startsWith("senha:"))
		{
			parameter.replace("senha:", "");
			senha = parameter;
		}
		else if (parameter.startsWith("url:"))
		{
			parameter.replace("url:", "");
			url = parameter;
		}

		else {
			Serial.println("#E_INVALID_CMD");
		}
	}

public:
	void save_config()
	{
		clearFile();
		writeFile("total_surge_cnt:" + String(total_surge));
		writeFile("device_state:" + String(device_state));
		writeFile("nome:" + String(nome));
		writeFile("rede:" + String(rede));
		writeFile("senha:" + String(senha));
		writeFile("url:" + String(url));
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
			line.replace("\n", "");
			line.replace("\r", "");
			Serial.println(line);
			save_parameter(line);
		}

		file_config.close();
	}
};
