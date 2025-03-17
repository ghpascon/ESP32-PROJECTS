#include "vars.h"

class OUTPUT_SURGE
{
public:
	void check()
	{
		get_post_str();
		check_post();
	}

private:
	String json;
	void get_post_str()
	{
		static bool last_lightning = false;
		static bool first_time = true;
		static String last_json = "";
		json = "{\"Dispositivo\":\"" + nome + "\",\"Tipo\":\"" + String(tipo) + "\",\"Bateria\":0,\"IdCliente\":" + String(id_cliente) + ",\"SurtoEletrico\":\"" + total_surge + "\",\"Dps\":\"" + String(device_state == 0 ? "OK" : (device_state == 1 ? "MANUT" : "INSP_IMEDIATA")) + "\",\"Raios\":\"" + String(qtd_raios) + "\"}";
		if (!first_time)
		{
			if (last_json == json)
				return;
			last_json = json;

			if (last_lightning)
			{
				last_lightning = false;
				return;
			}

			if (lightning_distance > 0)
			{
				lightning_distance = 0;
				last_lightning = true;
			}

			need_post = true;

			config_file_commands.save_config();
		}
		last_json = json;
		first_time = false;
	}

	void check_post()
	{
		if (!need_post)
			return;
		esp_post.post(json);
	}
};