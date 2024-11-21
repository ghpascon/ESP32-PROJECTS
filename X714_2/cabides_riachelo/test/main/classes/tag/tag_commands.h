#include "vars.h"

class TAG_COMMANDS
{
public:
	void add_tag(String current_epc, String current_tid, int current_ant, int current_rssi)
	{
		pins.ant_led_turn_on(current_ant);

		if (!read_on)
			return;

		if (antena[current_ant - 1].rssi < current_rssi)
			return;

		if (ignore_read && last_packs_read[0].indexOf(current_epc) != -1)
			return;

		if (always_send)
			display_current_tag(String(current_epc), String(current_tid), String(current_ant), String(current_rssi));

		for (int i = 0; i < max_tags; i++)
		{
			if (current_epc == tags[i].epc || current_tid == tags[i].tid)
				return;
			if (tags[i].epc == "" || tags[i].tid == "")
				break;
		}

		tags[current_tag].epc = current_epc;
		tags[current_tag].tid = current_tid;
		tags[current_tag].ant_number = current_ant;
		tags[current_tag].rssi = current_rssi;

		if (!always_send)
			display_current_tag(String(tags[current_tag].epc), String(tags[current_tag].tid), String(tags[current_tag].ant_number), String(tags[current_tag].rssi));
		
		current_tag_num();
	}

	void tag_data_display()
	{
		Serial.println("TOTAL: " + String(current_tag));
		for (int i = 0; i < max_tags; i++)
		{
			if (tags[i].epc == "" || tags[i].tid == "")
				break;

			Serial.println();
			Serial.println("TAG: " + String(i + 1));
			Serial.println("EPC: " + String(tags[i].epc));
			Serial.println("TID: " + String(tags[i].tid));
			Serial.println("ANT: " + String(tags[i].ant_number));
			Serial.println("RSSI: -" + String(tags[i].rssi));
			Serial.println();
		}
	}

	void clear_tags()
	{
		for (int i = 0; i < max_tags; i++)
		{
			tags[i].epc = "";
			tags[i].tid = "";
			tags[i].ant_number = 0;
			tags[i].rssi = 0;
		}
		current_tag = 0;
		Serial.println("#TAGS_CLEARED");
	}

private:
	void current_tag_num()
	{
		(current_tag < max_tags) ? current_tag++ : current_tag = 0;
	}

	void display_current_tag(String epc, String tid, String ant, String rssi)
	{
		Serial.println("#T+@" + epc + "|" + tid + "|" + ant + "|" + rssi);
	}
};
