#include "vars.h"
#include "serial_write_commands.h"
#include "serial_set_cmd.h"
#include "serial_save_tag.h"

class SERIAL_PORT : private serial_port_write, private serial_set_cmd, private serial_save_tag
{
public:
    void setup()
    {
        debug_mode ? Serial.begin(115200) : Serial.begin(115200, SERIAL_8N1, rx_x714, tx_x714);

        Serial1.begin(115200, SERIAL_8N1, rx_1, tx_1);
        Serial2.begin(57600, SERIAL_8N1, rx_reader_module, tx_reader_module);
    }

    void functions()
    {
        check_commands();
        check_esp_tags();
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

        else if (cmd == "#tags_data")
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

        else if (cmd.startsWith("#t+@"))
        {
            cmd.replace("#t+@", "");
            save_serial_tag(cmd);
        }

        else
        {
            Serial.println("#INVALID_CMD");
        }
    }

    void check_esp_tags()
    {
        if (!Serial1.available())
            return;
        String cmd = Serial1.readStringUntil('\n');
        cmd.toLowerCase();
        cmd.replace(" ", "");
        cmd.replace("\r", "");

        Serial.println("TAG REC: " + cmd);

        if (cmd.startsWith("#t+@"))
        {
            cmd.replace("#t+@", "");
            save_serial_tag(cmd);
        }
    }
};
