#include "vars.h"
#include "serial_write_commands.h"
#include "serial_set_cmd.h"

class MySerialCheck : private serial_port_write, private serial_set_cmd
{
public:
    void loop()
    {
        String cmd = myserial.check_serial();
        if (cmd != "")
            check_commands(cmd);
    }

    void check_commands(String cmd)
    {
        if (cmd == "#read:on")
        {
            read_on = true;
            myserial.write("#READ:ON");
        }
        else if (cmd == "#read:off")
        {
            read_on = false;
            myserial.write("#READ:OFF");
        }

        else if (cmd == "#get_tags")
        {
            tag_commands.tag_data_display();
        }

        else if (cmd == "#get_tags_all")
        {
            tag_commands.tag_data_display_all();
        }

        else if (cmd == "#clear")
        {
            tag_commands.clear_tags();
        }

        else if (cmd.startsWith("#write:"))
        {
            write_tag_cmd(cmd);
        }

        else if (cmd.startsWith("#password"))
        {
            reader_module.change_password(cmd);
        }

        else if (cmd.startsWith("#set_cmd:"))
        {
            cmd.replace("#set_cmd:", "");
            serial_set_all_cmd(cmd);
            reader_module.setup_reader();
        }

        else if (cmd == "#get_state")
        {
            myserial.write(read_on ? "#READING" : "#IDLE");
        }

        else if (cmd == "#get_power")
        {
            myserial.write("#POWER:" + String(antena[0].power));
        }

        else if (cmd == "#get_session")
        {
            myserial.write("#SESSION:" + String(session));
        }

        else if (cmd.startsWith("#hotspot:"))
        {
            hotspot_on = cmd.endsWith("on");
            reader_module.setup_reader();
        }

        else if (cmd == "#restart")
        {
            ESP.restart();
        }

        else if (cmd == "#get_serial")
        {
            uint64_t chipid = ESP.getEfuseMac();
            char id_str[13];
            sprintf(id_str, "%012llX", chipid);
            myserial.write("#SERIAL:" + String(id_str));
        }

        else
        {
            myserial.write("#INVALID_CMD");
        }
    }
};
