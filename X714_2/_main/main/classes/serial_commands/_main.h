#include "vars.h"
#include "serial_write_commands.h"
#include "serial_set_cmd.h"

class SERIAL_PORT : private serial_port_write, private serial_set_cmd
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial2.begin(57600, SERIAL_8N1, rx_reader_module, tx_reader_module);

        USB.VID(0x2222);
        USB.PID(0x0001);

        USB.manufacturerName("Smartx");
        USB.productName("X714");
        USB.serialNumber("X714");
        USB.usbAttributes(0x80);

        USB.begin();
        X714_USB.begin(115200);
    }

    void functions()
    {
        check_serial();
        verificar_write();
    }

private:
    void check_serial()
    {
        if (Serial.available())
        {
            String cmd = Serial.readStringUntil('\n');
            cmd.toLowerCase();
            cmd.replace(" ", "");
            cmd.replace("\r", "");
            cmd.replace("\n", "");
            check_commands(cmd);
        }

        if (X714_USB.available())
        {
            String cmd = X714_USB.readStringUntil('\n');
            cmd.toLowerCase();
            cmd.replace(" ", "");
            cmd.replace("\r", "");
            cmd.replace("\n", "");
            check_commands(cmd);
        }
    }

    void check_commands(String cmd)
    {
        if (cmd == "#read:on")
        {
            read_on = true;
            Serial.println("#READ:ON");
            X714_USB.println("#READ:ON");
        }
        else if (cmd == "#read:off")
        {
            read_on = false;
            Serial.println("#READ:OFF");
            X714_USB.println("#READ:OFF");
        }

        else if (cmd == "#get_tags")
        {
            tag_commands.tag_data_display();
        }

        else if (cmd == "#clear")
        {
            tag_commands.clear_tags();
        }

        else if (cmd.startsWith("#write:"))
        {
            write_tag_cmd(cmd);
        }

        else if (cmd.startsWith("#set_cmd:"))
        {
            cmd.replace("#set_cmd:", "");
            serial_set_all_cmd(cmd);
            reader_module.setup_reader();
        }

        else
        {
            Serial.println("#INVALID_CMD");
            X714_USB.println("#INVALID_CMD");
        }
    }
};
