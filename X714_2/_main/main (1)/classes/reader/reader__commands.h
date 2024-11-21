class commands_reader
{
public:
	void write_bytes(byte values[], byte lenght, byte crc1, byte crc2)
	{
		if (debug_mode)
			X714_USB.println("");

		for (int i = 0; i < lenght; i++)
		{
			if (debug_mode)
				X714_USB.println("SEND: " + String(values[i], HEX));
				
			Serial2.write(values[i]);
		}
		if (debug_mode)
		{
			X714_USB.println("SEND: " + String(crc1, HEX));
			X714_USB.println("SEND: " + String(crc2, HEX));
		}
		Serial2.write(crc1);
		Serial2.write(crc2);

		answer_rec = false;
		current_timeout_serial_rec = millis();
	}

	unsigned int uiCrc16Cal(unsigned char const *pucY, unsigned char ucX)
	{
		unsigned char ucI, ucJ;
		unsigned short int uiCrcValue = PRESET_VALUE;

		for (ucI = 0; ucI < ucX; ucI++)
		{
			uiCrcValue = uiCrcValue ^ *(pucY + ucI);
			for (ucJ = 0; ucJ < 8; ucJ++)
			{
				if (uiCrcValue & 0x0001)
				{
					uiCrcValue = (uiCrcValue >> 1) ^ POLYNOMIAL;
				}
				else
				{
					uiCrcValue = (uiCrcValue >> 1);
				}
			}
		}
		return uiCrcValue;
	}
};
