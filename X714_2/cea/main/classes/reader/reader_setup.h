class setup_commands_reader : public commands_reader
{
public:
	void start_reader()
	{
		byte start[] = {0x04, 0xff, 0x21};
		crcValue = uiCrc16Cal(start, sizeof(start));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(start, sizeof(start), crc1, crc2);
	}

	void set_reader_adress(byte adress)
	{
		byte reader_adress[] = {0x05, 0xff, 0x24, adress};
		crcValue = uiCrc16Cal(reader_adress, sizeof(reader_adress));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_adress, sizeof(reader_adress), crc1, crc2);
	}

	void reader_band()
	{
		byte band[] = {0x06, 0xff, 0x22, 0x31, 0x80};
		crcValue = uiCrc16Cal(band, sizeof(band));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(band, sizeof(band), crc1, crc2);
	}

	void reader_work_mode()
	{
		byte work_mode[] = {0x05, 0xff, 0x76, 0x00};
		crcValue = uiCrc16Cal(work_mode, sizeof(work_mode));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(work_mode, sizeof(work_mode), crc1, crc2);
	}

	void set_active_ant()
	{
		byte reader_active_ant[] = {
			0x05,
			0xff,
			0x3f,
			get_active_ant()};
		crcValue = uiCrc16Cal(reader_active_ant, sizeof(reader_active_ant));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_active_ant, sizeof(reader_active_ant), crc1, crc2);
	}
	byte get_active_ant()
	{
		byte ants = 0;
		for (int i = 0; i < ant_qtd; i++)
		{
			if (antena[i].active)
				ants += pow(2, i);
		}
		return ants;
	}

	void set_ant_power()
	{
		byte reader_ant_power[] = {
			0x08,
			0xff,
			0x2f,
			antena[0].power,
			antena[1].power,
			antena[2].power,
			antena[3].power};
		crcValue = uiCrc16Cal(reader_ant_power, sizeof(reader_ant_power));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_ant_power, sizeof(reader_ant_power), crc1, crc2);
	}

	void set_ant_check()
	{
		byte reader_ant_check[] = {
			0x05,
			0xff,
			0x66,
			0x01};
		crcValue = uiCrc16Cal(reader_ant_check, sizeof(reader_ant_check));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_ant_check, sizeof(reader_ant_check), crc1, crc2);
	}

	void set_ant_pulse()
	{
		byte reader_ant_pulse[] = {
			0x05,
			0xff,
			0x48,
			0x0f};
		crcValue = uiCrc16Cal(reader_ant_pulse, sizeof(reader_ant_pulse));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_ant_pulse, sizeof(reader_ant_pulse), crc1, crc2);
	}

	void set_retry_write(byte retry_times)
	{
		byte reader_retry_write_times[] = {
			0x05,
			0xff,
			0x7b,
			0x80 + retry_times};
		crcValue = uiCrc16Cal(reader_retry_write_times, sizeof(reader_retry_write_times));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_retry_write_times, sizeof(reader_retry_write_times), crc1, crc2);
	}
};
