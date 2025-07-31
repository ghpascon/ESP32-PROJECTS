#include "vars.h"

class TAG_COMMANDS
{
public:
	void add_tag(String current_epc, String current_tid, int current_ant, int current_rssi)
	{
		if (!read_on)
			return;

  		if (!startsWithAny(current_epc)) return;

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
		buzzer_time = millis();

		tags[current_tag].epc = current_epc;
		tags[current_tag].tid = current_tid;
		tags[current_tag].ant_number = current_ant;
		tags[current_tag].rssi = current_rssi;

		tags_table += "[\"" + String(current_tag + 1) + "\"" + "," + "\"" + String((current_epc.substring(0, current_epc.length() / 2)) + "<br>" + (current_epc.substring(current_epc.length() / 2))) + "\"" + "," + "\"" + String((current_tid.substring(0, current_tid.length() / 2)) + "<br>" + (current_tid.substring(current_tid.length() / 2))) + "\"" + "," + "\"" + String(current_ant) + "\"" + "," + "\"" + String(current_rssi) + "\"],";

		if (!always_send)
			display_current_tag(String(tags[current_tag].epc), String(tags[current_tag].tid), String(tags[current_tag].ant_number), String(tags[current_tag].rssi));

		current_tag_num();
	}

	void tag_data_display()
	{
		String tags_to_send = "#tags:";
		for (int i = 0; i < max_tags; i++)
		{
			if (tags[i].epc == "")
				break;
			tags_to_send += "@" + tags[i].epc;
		}
		Serial.println(tags_to_send);

		clear_tags();
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
		tags_table = "";
		Serial.println("#TAGS_CLEARED");
	}

private:
	void current_tag_num()
	{
		(current_tag < max_tags - 1) ? current_tag++ : current_tag = 0;
		if (current_tag == 0)
			tags_table = "";
	}

	void display_current_tag(String epc, String tid, String ant, String rssi)
	{
		Serial.println("#T+@" + epc + "|" + tid + "|" + ant + "|" + rssi);
	}


	bool startsWithAny(String current_epc) {
		if (prefix.length()==0) return true;
		current_epc.toLowerCase();  // modifica current_epc para minúsculo no local

		int start = 0;
		while (start < prefix.length()) {
			int commaIndex = prefix.indexOf(',', start);
			if (commaIndex == -1)
				commaIndex = prefix.length();

			String prefix_entry = prefix.substring(start, commaIndex);
			prefix_entry.trim();
			prefix_entry.toLowerCase();

			if (current_epc.startsWith(prefix_entry)) {
				return true;
			}
			start = commaIndex + 1;
		}
		return false;
	}
};
