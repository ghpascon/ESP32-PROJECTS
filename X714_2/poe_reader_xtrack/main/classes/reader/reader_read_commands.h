class reader_read_on_commands : public commands_reader
{
public:
    void read_on_command()
    {
        byte reader_read_on_command[] = {
            0x06,
            0xff,
            0x01,
            0x24,
            session};
        crcValue = uiCrc16Cal(reader_read_on_command, sizeof(reader_read_on_command));
        crc1 = crcValue & 0xFF;
        crc2 = (crcValue >> 8) & 0xFF;
        write_bytes(reader_read_on_command, sizeof(reader_read_on_command), crc1, crc2);
    }
};


