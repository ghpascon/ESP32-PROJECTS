class reader_write_commands : public commands_reader
{
public:
    void write_tag(byte *current_epc, byte *new_epc, byte *password, bool current_null)
    {
        if (!current_null)
        {
            byte reader_write_command[] = {
                0x24,
                0xff,
                0x03,
                0x06,
                0x06,

                current_epc[0],
                current_epc[1],
                current_epc[2],
                current_epc[3],
                current_epc[4],
                current_epc[5],
                current_epc[6],
                current_epc[7],
                current_epc[8],
                current_epc[9],
                current_epc[10],
                current_epc[11],

                0x01,
                0x02,

                new_epc[0],
                new_epc[1],
                new_epc[2],
                new_epc[3],
                new_epc[4],
                new_epc[5],
                new_epc[6],
                new_epc[7],
                new_epc[8],
                new_epc[9],
                new_epc[10],
                new_epc[11],

                password[0],
                password[1],
                password[2],
                password[3]};

            crcValue = uiCrc16Cal(reader_write_command, sizeof(reader_write_command));
            crc1 = crcValue & 0xFF;
            crc2 = (crcValue >> 8) & 0xFF;
            write_bytes(reader_write_command, sizeof(reader_write_command), crc1, crc2);
        }
        else
        {
            byte reader_write_command[] = {
                0x15,
                0xff,
                0x04,
                0x06,

                password[0],
                password[1],
                password[2],
                password[3],

                new_epc[0],
                new_epc[1],
                new_epc[2],
                new_epc[3],
                new_epc[4],
                new_epc[5],
                new_epc[6],
                new_epc[7],
                new_epc[8],
                new_epc[9],
                new_epc[10],
                new_epc[11]};

            crcValue = uiCrc16Cal(reader_write_command, sizeof(reader_write_command));
            crc1 = crcValue & 0xFF;
            crc2 = (crcValue >> 8) & 0xFF;
            write_bytes(reader_write_command, sizeof(reader_write_command), crc1, crc2);
        }
    }

    void change_password(String cmd)
    {
        myserial.write("Received: " + cmd);

        // Remove the prefix using replace
        cmd.replace("#password:", "");

        // Split parameters
        int idx1 = cmd.indexOf('|');
        int idx2 = cmd.indexOf('|', idx1 + 1);

        if (idx1 == -1 || idx2 == -1)
        {
            myserial.write("Invalid format: Missing separators '|'");
            return;
        }

        String param1 = cmd.substring(0, idx1);
        String param2 = cmd.substring(idx1 + 1, idx2);
        String param3 = cmd.substring(idx2 + 1);

        // Validation: lengths and hex characters
        if (param1.length() != 24 || param2.length() != 8 || param3.length() != 8)
        {
            myserial.write("Invalid parameter length");
            return;
        }

        // Check each character is hex
        String allParams[] = {param1, param2, param3};
        for (int i = 0; i < 3; i++)
        {
            for (char c : allParams[i])
            {
                if (!isHexadecimalDigit(c))
                {
                    myserial.write("Invalid hex digit in parameter " + String(i + 1));
                    return;
                }
            }
        }

        // Store into 2D char array
        char password_data[3][25]; // 24 chars + null terminator
        param1.toCharArray(password_data[0], sizeof(password_data[0]));
        param2.toCharArray(password_data[1], sizeof(password_data[1]));
        param3.toCharArray(password_data[2], sizeof(password_data[2]));
    }
};
