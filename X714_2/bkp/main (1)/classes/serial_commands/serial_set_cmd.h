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

        if (cmd.startsWith("set_ant:"))
        {
            cmd.replace("set_ant:", "");
            serial_set_ant(cmd);
        }

        else if (cmd.startsWith("session:"))
        {
            cmd.replace("session:", "");
            session = cmd.toInt();
            if (session > max_session)
                session = 0x00;
        }

        else if (cmd.startsWith("set_power_all:"))
        {
            cmd.replace("set_power_all:", "");
            antena_commands.set_power_all(cmd.toInt());
        }

        else if (cmd == "start_reading:off")
        {
            start_reading = false;
        }
        else if (cmd == "start_reading:on")
        {
            start_reading = true;
        }

        else if (cmd == "gpi_start:off")
        {
            gpi_start = false;
        }
        else if (cmd == "gpi_start:on")
        {
            gpi_start = true;
        }
        else if (cmd.startsWith("gpi_stop_delay:"))
        {
            cmd.replace("gpi_stop_delay:", "");
            gpi_stop_delay = cmd.toInt();
        }

        else if (cmd == "ignore_read:off")
        {
            ignore_read = false;
        }
        else if (cmd == "ignore_read:on")
        {
            ignore_read = true;
        }

        else if (cmd == "always_send:off")
        {
            always_send = false;
        }
        else if (cmd == "always_send:on")
        {
            always_send = true;
        }

        else
        {
            Serial.println("#INVALID_CMD");
        }
    }
    
    void serial_set_ant(String cmd)
    {
        const String antena_data_prefix = ",";
        int start_antena_data;

        start_antena_data = cmd.indexOf(antena_data_prefix);
        const int current_ant = cmd.substring(0, start_antena_data).toInt();
        cmd = cmd.substring(start_antena_data + 1);

        start_antena_data = cmd.indexOf(antena_data_prefix);
        const String current_active = cmd.substring(0, start_antena_data);
        cmd = cmd.substring(start_antena_data + 1);

        start_antena_data = cmd.indexOf(antena_data_prefix);
        byte current_power = cmd.substring(0, start_antena_data).toInt();
        cmd = cmd.substring(start_antena_data + 1);

        byte current_rssi = cmd.toInt();

        if (current_power > max_power)
            current_power = max_power;
        if (current_power < min_power)
            current_power = min_power;
        if (current_rssi < min_rssi)
            current_rssi = min_rssi;

        antena_commands.set_antena(current_ant, (current_active == "on" ? true : false), current_power, current_rssi);
    }
};
