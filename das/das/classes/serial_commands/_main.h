#include "vars.h"

class SERIAL_PORT
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial1.begin(115200, SERIAL_8N1, rx1_pin, tx1_pin);
        Serial2.begin(115200, SERIAL_8N1, rx2_pin, tx2_pin);
    }

    void send_data()
    {
        Serial1.println("#PERFIL:" + String(mode - 2));
    }

    void check()
    {
        if (!Serial.available())
            return;
        String cmd = Serial.readStringUntil('\n');
        cmd.replace(" ", "");
        cmd.replace("\r", "");
        cmd.replace("\n", "");
        cmd.toLowerCase();
        check_cmd(cmd);
    }

private:
    void check_cmd(String cmd)
    {
        if (cmd.startsWith("#box:"))
        {
            cmd.replace("#box:", "");
            int sep = cmd.indexOf(",");
            box_num = cmd.substring(0, sep);
            box_qtd = cmd.substring(sep + 1).toInt();
        }
    }
};
