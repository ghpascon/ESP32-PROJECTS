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
		if (need_post)
			return;

		static String last_json = "";
		json = "{\"name\":\"" + nome + "\",\"total_surge\":\"" + total_surge + "\",\"device_state\":\"" + String(device_state) + "\"}";
		if (last_json == json)
			return;
		last_json = json;

		need_post = true;

		config_file_commands.save_config();
	}

	void check_post()
	{
		if (!need_post)
			return;
		esp_post.post(json);
	}
};