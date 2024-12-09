class reader_write_commands : public commands_reader
{
public:
    void write_tag(byte *current_epc, byte *new_epc, byte *password)
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
};
