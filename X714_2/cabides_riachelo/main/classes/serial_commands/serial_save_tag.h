class serial_save_tag
{
public:
    void save_serial_tag(String cmd)
    {
        const String sep_string("|");

        int sep_index = cmd.indexOf(sep_string);
        const String current_epc = cmd.substring(0, sep_index);
        cmd = cmd.substring(1 + sep_index);

        sep_index = cmd.indexOf(sep_string);
        const String current_tid = cmd.substring(0, sep_index);
        cmd = cmd.substring(1 + sep_index);

        sep_index = cmd.indexOf(sep_string);
        const String current_ant = cmd.substring(0, sep_index);
        const String current_rssi = cmd.substring(1 + sep_index);

        if (debug_mode)
        {
            Serial.println(current_epc);
            Serial.println(current_tid);
            Serial.println(current_ant);
            Serial.println(current_rssi);
        }

        tag_commands.add_tag(current_epc, current_tid, current_ant.toInt(), current_rssi.toInt(),false);
    }
};
