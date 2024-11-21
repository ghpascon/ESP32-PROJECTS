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

class reader_read_off_commands : public commands_reader
{
public:
    void read_off_command()
    {
        return;
        byte reader_read_off_command[] = {
            0x04,
            0xff,
            0x93};
        crcValue = uiCrc16Cal(reader_read_off_command, sizeof(reader_read_off_command));
        crc1 = crcValue & 0xFF;
        crc2 = (crcValue >> 8) & 0xFF;
        write_bytes(reader_read_off_command, sizeof(reader_read_off_command), crc1, crc2);
    }
};
