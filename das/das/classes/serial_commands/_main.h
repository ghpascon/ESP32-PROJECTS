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
        check_serial();
        check_serial1();
    }

private:
    void check_serial()
    {
        if (!Serial.available())
            return;
        String cmd_original = Serial.readStringUntil('\n');
        cmd_original.replace("\r", "");
        cmd_original.replace("\n", "");
        String cmd = cmd_original;
        cmd.replace(" ", "");
        cmd.toLowerCase();
        check_cmd(cmd, cmd_original);
    }

    void check_serial1()
    {
        if (!Serial1.available())
            return;
        String cmd_original = Serial1.readStringUntil('\n');


        cmd_original.replace("\r", "");
        cmd_original.replace("\n", "");
        cmd_original.replace("/n", "");

        Serial.println("RECEIVED: " + cmd_original);

        String cmd = cmd_original;
        cmd.replace(" ", "");
        cmd.toLowerCase();
        check_cmd(cmd, cmd_original);
    }

    void check_cmd(String cmd, String cmd_original)
    {
        if (cmd.startsWith("#box:"))
        {
            cmd.replace("#box:", "");
            int sep = cmd.indexOf("|");
            box_num = cmd.substring(0, sep);
            box_qtd = cmd.substring(sep + 1).toInt();
            Serial.println("#BOX:" + box_num + "|" + String(box_qtd));
        }

        else if (cmd.startsWith("#cx:"))
        {
            cmd.replace("#cx:", "");
            cx_ok = cmd.startsWith("ok");
            cx_erro = !cx_ok;

            state_msg = cmd_original.substring(cmd_original.indexOf("|") + 1);

            Serial.println("#CX:" + cx_ok ? "OK" : "ERROR");
            Serial.println("MSG: " + state_msg);
        }

        else if (cmd.startsWith("#step:"))
        {
            if (!debug_mode)
                return;
            cmd.replace("#step:", "");
            step = cmd.toInt();
        }

        else if (cmd.startsWith("#speed:"))
        {
            cmd.replace("#speed:", "");
            speed = cmd.toInt();
        }
    }
};
