#include "vars.h"
#include "serial_write_commands.h"
#include "serial_set_cmd.h"

class SERIAL_PORT : private serial_port_write, private serial_set_cmd
{
public:
    void setup()
    {
        (debug_mode || one_ant) ? Serial.begin(115200) : Serial.begin(115200, SERIAL_8N1, rx_x714, tx_x714);
        Serial2.begin(57600, SERIAL_8N1, rx_reader_module, tx_reader_module);
    }

    void functions()
    {
        check_commands();
        verificar_write();
    }

    void check_commands()
    {
        if (!Serial.available())
            return;
        String cmd = Serial.readStringUntil('\n');
        cmd.toLowerCase();
        cmd.replace(" ", "");
        cmd.replace("\r", "");

        if (cmd == "#read:on")
        {
            read_on = true;
            Serial.println("#READ:ON");
        }
        else if (cmd == "#read:off")
        {
            read_on = false;
            Serial.println("#READ:OFF");
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
        }
    }
};
