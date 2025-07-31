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
		static bool last_band_state = false;
		static unsigned long current_last_band = 0;
		const int interval = 500;

		byte band[5];
		if (!setup_done)
		{
			byte temp[] = {0x06, 0xff, 0x22, 0xf4, 0x1a};
			// byte temp[] = {0x06, 0xff, 0x22, 0x31, 0x80};
			memcpy(band, temp, sizeof(temp));
		}
		else
		{
			if (!read_on)
				return;

			if (millis() - current_last_band < interval)
				return;

			current_last_band = millis();
			last_band_state = !last_band_state;

			if (last_band_state)
			{
				byte temp[] = {0x06, 0xff, 0x22, 0xcb, 0x00};
				memcpy(band, temp, sizeof(temp));
			}
			else
			{
				byte temp[] = {0x06, 0xff, 0x22, 0xf4, 0x1a};
				memcpy(band, temp, sizeof(temp));
			}
		}

		uint16_t crcValue = uiCrc16Cal(band, sizeof(band));
		byte crc1 = crcValue & 0xFF;
		byte crc2 = (crcValue >> 8) & 0xFF;

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

	void reader_session()
	{
		byte reader_session[] = {
			0x0d,
			0xff,
			0x75,
			0x00,
			0x00,
			0x01,
			0x44,
			session,
			0x01,
			0x00,
			0x00,
			0x00};
		crcValue = uiCrc16Cal(reader_session, sizeof(reader_session));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_session, sizeof(reader_session), crc1, crc2);
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
		if (one_ant)
			return 0x01;
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
		if (one_ant)
		{
			byte reader_ant_power[] = {
				0x05,
				0xff,
				0x2f,
				antena[0].power};
			crcValue = uiCrc16Cal(reader_ant_power, sizeof(reader_ant_power));
			crc1 = crcValue & 0xFF;
			crc2 = (crcValue >> 8) & 0xFF;
			write_bytes(reader_ant_power, sizeof(reader_ant_power), crc1, crc2);
		}
		else
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
	}

	void set_ant_check()
	{
		byte reader_ant_check[] = {
			0x05,
			0xff,
			0x66,
			0x00};
		crcValue = uiCrc16Cal(reader_ant_check, sizeof(reader_ant_check));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_ant_check, sizeof(reader_ant_check), crc1, crc2);
	}

	void set_reader_time()
	{
		byte reader_time[] = {
			0x05,
			0xff,
			0x25,
			0x00};
		crcValue = uiCrc16Cal(reader_time, sizeof(reader_time));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_time, sizeof(reader_time), crc1, crc2);
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

	void query_parameters()
	{
		byte reader_query[] = {
			0x09,
			0xff,
			0xea,
			0x00,
			0x07,
			0x00,
			0x02,
			0x00};
		crcValue = uiCrc16Cal(reader_query, sizeof(reader_query));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_query, sizeof(reader_query), crc1, crc2);
	}

	void set_write_power(byte power)
	{
		byte reader_time[] = {
			0x05,
			0xff,
			0x79,
			0x80 + power};
		crcValue = uiCrc16Cal(reader_time, sizeof(reader_time));
		crc1 = crcValue & 0xFF;
		crc2 = (crcValue >> 8) & 0xFF;
		write_bytes(reader_time, sizeof(reader_time), crc1, crc2);
	}
};
