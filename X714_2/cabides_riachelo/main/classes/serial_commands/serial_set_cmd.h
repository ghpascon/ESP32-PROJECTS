class serial_set_cmd
{
public:
    void serial_set_all_cmd(String cmd)
    {
        const String set_cmd_sep = "|";
        String current_cmd;
        while (true)
        {
            int cmd_sep_index = cmd.indexOf(set_cmd_sep);

            if (cmd_sep_index = -1)
            {
                current_cmd = cmd;
                set_cmd_handler(current_cmd);
                break;
            }
            else
            {
                current_cmd = cmd.substring(0, cmd_sep_index);
                set_cmd_handler(current_cmd);
                cmd = cmd.substring(cmd_sep_index + 1);
            }
        }
    }

private:
    void set_cmd_handler(String cmd)
    {
        if (debug_mode)
            Serial.println(cmd);

        if (cmd.startsWith("set_power_all:"))
        {
            cmd.replace("set_power_all:", "");
            antena_commands.set_power_all(cmd.toInt());
        }

        else
        {
            Serial.println("#INVALID_CMD");
        }
    }
};
