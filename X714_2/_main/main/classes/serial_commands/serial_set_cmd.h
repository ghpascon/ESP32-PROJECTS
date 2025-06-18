class serial_set_cmd {
public:
    void serial_set_all_cmd(String cmd) {
        const String set_cmd_sep = "|";
        String current_cmd;

        while (true) {
            int cmd_sep_index = cmd.indexOf(set_cmd_sep);

            if (cmd_sep_index == -1) {
                current_cmd = cmd;
                set_cmd_handler(current_cmd);
                break;
            } else {
                current_cmd = cmd.substring(0, cmd_sep_index);
                set_cmd_handler(current_cmd);
                cmd = cmd.substring(cmd_sep_index + 1);
            }
        }
    }

private:
    void handle_boolean_command(const String& cmd, const String& prefix, bool& variable, bool& matched) {
        if (cmd.startsWith(prefix)) {
            variable = cmd.endsWith("on");
            matched = true;
        }
    }

    void set_cmd_handler(String cmd) {
        bool cmd_ok = true;

        Serial.print("#CMD: " + cmd);
        if (!simple_send)
            X714_USB.print("#CMD: " + cmd);

        if (cmd.startsWith("set_ant:")) {
            cmd.replace("set_ant:", "");
            serial_set_ant(cmd);
        }

        else if (cmd.startsWith("session:")) {
            cmd.replace("session:", "");
            session = cmd.toInt();
            if (session > max_session)
                session = 0x00;
        }

        else if (cmd.startsWith("read_power:")) {
            cmd.replace("read_power:", "");
            antena_commands.set_power_all(cmd.toInt());
        }

        else if (cmd.startsWith("write_power:")) {
            cmd.replace("write_power:", "");
            write_power = constrain(cmd.toInt(), min_power, max_power);
        }

        else if (cmd.startsWith("gpi_stop_delay:")) {
            cmd.replace("gpi_stop_delay:", "");
            gpi_stop_delay = cmd.toInt();
        }

        else {
            // Verifica comandos booleanos
            bool matched = false;
            handle_boolean_command(cmd, "start_reading:", start_reading, matched);
            handle_boolean_command(cmd, "gpi_start:", gpi_start, matched);
            handle_boolean_command(cmd, "ignore_read:", ignore_read, matched);
            handle_boolean_command(cmd, "always_send:", always_send, matched);
            handle_boolean_command(cmd, "simple_send:", simple_send, matched);

            if (!matched)
                cmd_ok = false;
        }

        Serial.println(cmd_ok ? "#SET_CMD:OK" : "#SET_CMD:NOK");
        if (!simple_send)
            X714_USB.println(cmd_ok ? "#SET_CMD:OK" : "#SET_CMD:NOK");
    }

    void serial_set_ant(String cmd) {
        const String antena_data_prefix = ",";
        int start_antena_data;

        start_antena_data = cmd.indexOf(antena_data_prefix);
        int current_ant = cmd.substring(0, start_antena_data).toInt();
        cmd = cmd.substring(start_antena_data + 1);

        start_antena_data = cmd.indexOf(antena_data_prefix);
        String current_active = cmd.substring(0, start_antena_data);
        cmd = cmd.substring(start_antena_data + 1);

        start_antena_data = cmd.indexOf(antena_data_prefix);
        byte current_power = cmd.substring(0, start_antena_data).toInt();
        cmd = cmd.substring(start_antena_data + 1);

        byte current_rssi = cmd.toInt();

        current_power = constrain(current_power, min_power, max_power);
        current_rssi = max(current_rssi, min_rssi);

        antena_commands.set_antena(
            current_ant,
            (current_active == "on"),
            current_power,
            current_rssi
        );
    }
};
