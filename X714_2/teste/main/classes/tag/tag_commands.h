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

		tags_table += "[\"" + String(current_tag + 1) + "\"" + "," + "\"" + String((current_epc.substring(0, current_epc.length() / 2)) + "<br>" + (current_epc.substring(current_epc.length() / 2))) + "\"" + "," + "\"" + String((current_tid.substring(0, current_tid.length() / 2)) + "<br>" + (current_tid.substring(current_tid.length() / 2))) + "\"" + "," + "\"" + String(current_ant) + "\"" + "," + "\"" + String(current_rssi) + "\"],";

		if (!always_send)
			display_current_tag(String(tags[current_tag].epc), String(tags[current_tag].tid), String(tags[current_tag].ant_number), String(tags[current_tag].rssi));

		current_tag_num();
	}

	void tag_data_display()
	{
		X714_USB.println("TOTAL: " + String(current_tag));
		for (int i = 0; i < max_tags; i++)
		{
			if (tags[i].epc == "" || tags[i].tid == "")
				break;

			X714_USB.println();
			X714_USB.println("TAG: " + String(i + 1));
			X714_USB.println("EPC: " + String(tags[i].epc));
			X714_USB.println("TID: " + String(tags[i].tid));
			X714_USB.println("ANT: " + String(tags[i].ant_number));
			X714_USB.println("RSSI: -" + String(tags[i].rssi));
			X714_USB.println();
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
		tags_table = "";
		X714_USB.println("#TAGS_CLEARED");
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
		X714_USB.println("#T+@" + epc + "|" + tid + "|" + ant + "|" + rssi);
	}
};