class serial_reader
{
public:
	void check_serial()
	{
		if (!Serial2.available())
			return;

		const int full_cmd_timeout = 3000;
		unsigned long current_full_cmd_timeout = millis();

		answer_rec = true;
		String cmd_rec = "";
		current_timeout_serial_rec = millis();
		while (millis() - current_timeout_serial_rec < timeout_serial_rec || millis() - current_full_cmd_timeout > full_cmd_timeout)
		{
			if (!Serial2.available())
				continue;
			byte cmd = Serial2.read();
			cmd_rec += String((cmd < 0x10) ? "0" : "") + String(cmd, HEX);
			current_timeout_serial_rec = millis();
		}
		cmd_handler(cmd_rec);
	}

private:
	void cmd_handler(String cmd)
	{
		String status = cmd.substring(2, 4);
		String reader_cmd = cmd.substring(4, 6);

		if (status == "00")
		{
			if (reader_cmd == "01" && cmd.substring(6, 8) == "f8")
			{
				myserial.write("#ANT_ERROR: ");
			}

			if (reader_cmd == "06")
			{
				if (cmd.substring(6, 8) == "00")
				{
					myserial.write("#LOCK_OK");
				}
				else
				{
					myserial.write("#LOCK_NOK");
				}
			}

			else if (reader_cmd == "03" || reader_cmd == "04")
			{
				if (cmd.substring(6, 8) == "00")
				{
					myserial.write("#TAG_WRITE_SUCESSO");
				}
				else
				{
					myserial.write("#TAG_WRITE_ERRO");
				}
			}

			step++;
		}
		else
		{
			myserial.write("#ERRO: " + status);
			return;
		}

		// temperatura
		if (reader_cmd == "01")
		{
			tag_command(cmd);
		}
		else if (reader_cmd == "92")
		{
			String current_temp = cmd.substring(cmd.length() - 6, cmd.length() - 4);
			temperatura = (byte)strtol(current_temp.c_str(), NULL, 16);
			myserial.write("#TEMPERATURA:" + String(temperatura, DEC));
		}
	}

	void tag_command(String tag_cmd)
	{
		const String tag_data_prefix = "21000103";
		while (true)
		{
			const int start_tag_data = tag_cmd.indexOf(tag_data_prefix);
			if (start_tag_data == -1)
				break;

			tag_cmd = tag_cmd.substring(start_tag_data + tag_data_prefix.length());
			if (tag_cmd.length() < 57)
				break;

			if (tag_cmd.substring(4, 6).toInt() != 98)
				continue;

			const String current_epc = tag_cmd.substring(6, 30);
			const String current_tid = tag_cmd.substring(30, 54);

			int current_ant = tag_cmd.substring(0, 2).toInt();
			if (current_ant == 4)
				current_ant = 3;
			if (current_ant == 8)
				current_ant = 4;

			const int current_rssi = strtol(tag_cmd.substring(54, 56).c_str(), NULL, 16);
			tag_commands.add_tag(current_epc, current_tid, current_ant, current_rssi);
		}
	}
};
