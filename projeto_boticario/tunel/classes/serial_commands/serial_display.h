class serial_display
{
public:
    void check_serial_display()
    {
        if (!Serial1.available())
            return;
        String cmd = Serial1.readStringUntil('\n');
        cmd.replace(" ", "");
        cmd.replace("\r", "");
        cmd.replace("\n", "");
        cmd.toLowerCase();
        Serial.println(cmd);
        if (cmd.startsWith("#set_speed:"))
        {
            set_speed(cmd);
        }
        else if (cmd.startsWith("#set_retry:"))
        {
            set_retry(cmd);
        }
        else if (cmd == "#get_status")
        {
            send_status();
        }

        config_file_commands.save_config();
    }

    void send_status()
    {
        Serial1.println("#SPEED_SELECTED:" + String(speed));
        Serial1.println("#RETRY_SELECTED:" + String(retry_cnt));
    }

private:
    void set_speed(String cmd)
    {
        cmd.replace("#set_speed:", "");
        if (cmd.toInt() >= 1 && cmd.toInt() <= 4)
            speed = cmd.toInt();
        Serial1.println("#SPEED_SELECTED:" + String(speed));
    }

    void set_retry(String cmd)
    {
        cmd.replace("#set_retry:", "");
        if (cmd.toInt() >= 0 && cmd.toInt() <= 10)
            retry_cnt = cmd.toInt();
        Serial1.println("#RETRY_SELECTED:" + String(retry_cnt));
    }
};
