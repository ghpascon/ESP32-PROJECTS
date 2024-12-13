#include "vars.h"
#include "serial_display.h"

class SERIAL_PORT : private serial_display
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial1.begin(115200, SERIAL_8N1, rx1_pin, tx1_pin);
    }

    void send_sts()
    {
        send_status();
    }

    void functions()
    {
        check_serial();
        check_serial_display();
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

        if (cmd.startsWith("#cx:"))
        {
            cmd.replace("#cx:", "");
            cx_ok = cmd.startsWith("ok");
            cx_erro = !cx_ok;
        }
    }
};
