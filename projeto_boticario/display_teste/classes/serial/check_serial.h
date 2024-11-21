class check_serial
{
public:
    void check_serial_cmd()
    {
        if (!Serial2.available())
            return;
        String cmd = Serial2.readStringUntil('\n');
        cmd.replace(" ", "");
        cmd.toLowerCase();
        if (cmd.startsWith("#speed_selected:"))
        {
            set_speed(cmd);
        }
        else if (cmd.startsWith("#retry_selected:"))
        {
            set_retry(cmd);
        }
    }

private:
    void set_speed(String cmd)
    {
        cmd.replace("#speed_selected:", "");
        speed = cmd.toInt();
    }

    void set_retry(String cmd)
    {
        cmd.replace("#retry_selected:", "");
        retry = cmd.toInt();
    }
};
