#include "vars.h"

class LAST_PACKS
{
public:
	void clear()
	{
		for (int i = 0; i < max_packs; i++)
		{
			last_packs_read[i] = "";
		}
	}

	void save()
	{
		String serial_pack = "#P_:";
		int removed_tags = 0;
		int total_tags = 0;

		for (int i = max_packs - 1; i > 0; i--)
		{
			last_packs_read[i] = last_packs_read[i - 1];
		}

		last_packs_read[0] = "TOTAL: {total}\nREMOVIDO: {removido}\nRESULTADO {result}";
		for (int i = 0; i < max_tags; i++)
		{
			if (tags[i].epc == "" || tags[i].tid == "")
			{
				last_packs_read[0].replace("{total}", String(i));
				total_tags = i;
				break;
			}

			if (tags[i].ant_number != 1 && tags[i].ant_number != 2)
			{
				last_packs_read[0] += "\n" + tags[i].epc + "|" + tags[i].tid;
				serial_pack += tags[i].epc + ",";
			}
			else
			{
				removed_tags++;
			}
		}

		last_packs_read[0].replace("{total}", String(max_tags));
		last_packs_read[0].replace("{removido}", String(removed_tags));
		last_packs_read[0].replace("{result}", String(total_tags - removed_tags));
		Serial.println(serial_pack);

		for (int i = 0; i < max_packs; i++)
		{
			if (!debug_mode)
				break;
			Serial.println();
			Serial.println(last_packs_read[i]);
			Serial.println();
		}
	}
};
