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
		String serial_pack = "#PACK:";
		for (int i = max_packs - 1; i > 0; i--)
		{
			last_packs_read[i] = last_packs_read[i - 1];
		}

		last_packs_read[0] = "TOTAL: {total}";
		for (int i = 0; i < max_tags; i++)
		{
			if (tags[i].epc == "" || tags[i].tid == "")
			{
				last_packs_read[0].replace("{total}", String(i));
				break;
			}
			last_packs_read[0] += "\n" + tags[i].epc + "|" + tags[i].tid;
			serial_pack += "@" + tags[i].epc + "|" + tags[i].tid;
		}
		last_packs_read[0].replace("{total}", String(max_tags));
		myserial.write(serial_pack);
	}
};
