class periodic_commands_reader : public commands_reader
{
public:
	void get_temp()
	{
		byte temp[] = {0x04, 0xff, 0x92};
		crcValue = uiCrc16Cal(temp, sizeof(temp));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(temp, sizeof(temp), crc1, crc2);
	}
};
