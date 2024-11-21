#include "vars.h"
#include "serial_write_commands.h"
#include "serial_set_cmd.h"

class SERIAL_PORT : private serial_port_write, private serial_set_cmd
{
public:
    void setup()
    {
        USB.VID(0x2222);
        USB.PID(0x0001);
        USB.manufacturerName("Smartx");
        USB.productName("X714");
        USB.usbAttributes(115200);
        USB.begin();
        X714_USB.begin(115200);

        Serial2.begin(57600, SERIAL_8N1, rx_reader_module, tx_reader_module);

        delay(500);

        while (Serial2.available())
            byte trash = Serial2.read();
    }

    void functions()
    {
        check_commands();
        verificar_write();
    }

    void check_commands()
    {
        if (!X714_USB.available())
            return;
        String cmd = X714_USB.readStringUntil('\n');
        cmd.toLowerCase();
        cmd.replace(" ", "");
        cmd.replace("\r", "");

        if (cmd == "#read:on")
        {
            read_on = true;
            X714_USB.println("#READ:ON");
        }
        else if (cmd == "#read:off")
        {
            read_on = false;
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
        }

        else
        {
            X714_USB.println("#INVALID_CMD");
        }
    }
};
