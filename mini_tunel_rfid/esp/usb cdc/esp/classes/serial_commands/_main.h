#include "vars.h"

class SERIAL_PORT
{
public:
    void setup()
    {
        Serial.begin(115200);
        USB.VID(0x2222);
        USB.PID(0x0001);

        USB.manufacturerName("Smartx");
        USB.productName("X714");
        USB.serialNumber("X714");
        USB.usbAttributes(0x80);

        USB.begin();
        X714_USB.begin(9600);
        Serial2.begin(115200, SERIAL_8N1, rx2_pin, tx2_pin);
    }

    void send_data()
    {
        if (client == 1)
            return;

        X714_USB.println("#PERFIL:" + String(mode - 2));
    }

    void check()
    {
        check_serial();
        check_X714_USB();
    }

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

    void check_X714_USB()
    {
        if (!X714_USB.available())
            return;
        String cmd_original = X714_USB.readStringUntil('\n');

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
        cmd = regex_cmd(cmd);
        if (cmd.startsWith("#box:"))
        {
            cmd.replace("#box:", "");
            int sep = cmd.indexOf("|");
            box_num = cmd.substring(0, sep);
            box_num.toUpperCase();
            box_qtd = cmd.substring(sep + 1).toInt();
            Serial.println("#BOX:" + box_num + "|" + String(box_qtd));
        }

        else if (cmd.startsWith("#cx:"))
        {
            cmd.replace("#cx:", "");
            Serial.println(cmd);
            cx_ok = cmd.startsWith("ok");
            cx_erro = cmd.startsWith("erro");

            state_msg = cmd_original.substring(cmd_original.indexOf("|") + 1);

            if (cx_erro || cx_ok)
            {
                Serial.println("#CX:" + String(cx_ok ? "OK" : "ERROR"));
                Serial.println("MSG: " + state_msg);
            }
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

        else if (cmd == "#get_results")
        {
            Serial.println("#BOX_RESULTS:" + String(box_results[0]) + "," + String(box_results[1]) + "," + String(box_results[2]));
        }

        else if (cmd == "#clear_results")
        {
            Serial.println("#CLEAR_DATA");
            box_results[0] = 0;
            box_results[1] = 0;
            box_results[2] = 0;
        }

        else if (cmd.startsWith("#bx_results:"))
        {
            cmd.replace("#bx_results:", "");
            const String sep = ",";
            int sep_index;

            sep_index = cmd.indexOf(sep);
            box_results[0] = cmd.substring(0, sep_index).toInt();
            cmd = cmd.substring(1 + sep_index);

            sep_index = cmd.indexOf(sep);
            box_results[1] = cmd.substring(0, sep_index).toInt();
            box_results[2] = cmd.substring(1 + sep_index).toInt();
        }
    }

private:
    String regex_cmd(String cmd)
    {
        String allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,;:!?(){}[]@#$%^&*_+=/|-";
        String reg_cmd = "";

        for (int i = 0; i < cmd.length(); i++)
        {
            if (allowedChars.indexOf(cmd[i]) != -1)
            {
                reg_cmd += cmd[i];
            }
        }

        return reg_cmd;
    }
};
