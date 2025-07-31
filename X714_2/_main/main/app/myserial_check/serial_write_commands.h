class serial_port_write
{
public:
    void write_tag_cmd(String cmd)
    {
        if (read_on)
        {
            last_read_on = true;
            read_on = false;
        }

        const byte tag_size = 24;
        const byte password_size = 8;

        cmd.replace("#write:", "");
        int sep_index = cmd.indexOf("|");
        if (sep_index == -1)
        {
            myserial.write("#E_NO_SEP");
            return;
        }
        current_epc = cmd.substring(0, sep_index);

        cmd = cmd.substring(sep_index + 1);
        int passowrd_index = cmd.indexOf("|");
        if (sep_index == -1)
        {
            myserial.write("#E_NO_PASSWORD");
            return;
        }
        new_epc = cmd.substring(0, passowrd_index);
        password = cmd.substring(passowrd_index + 1);

        if (password.length() != password_size)
        {
            myserial.write("#E_PASSWORD_LENGTH");
            return;
        }
        if ((current_epc != "null" && current_epc.length() != tag_size) || new_epc.length() != tag_size)
        {
            myserial.write("#E_TAG_LENGTH");
            return;
        }

        write_tag_on = true;
    }

    void verificar_write()
    {
        if (!write_tag_on)
            return;
        if (!answer_rec)
            return;
        gerar_bytes(current_epc, new_epc, password, current_epc == "null");
        write_tag_on = false;

        if (last_read_on)
        {
            last_read_on = false;
            read_on = true;
        }
    }

private:
    void gerar_bytes(String current_epc, String new_epc, String password, bool current_null)
    {
        const byte byte_tag_count = 12;
        const byte byte_password_count = 4;

        byte current_epc_array[byte_tag_count];

        if (!current_null)
        {
            for (int i = 0; i < byte_tag_count; i++)
            {
                String current_epc_byte = current_epc.substring(i * 2, i * 2 + 2);
                current_epc_array[i] = (byte)strtol(current_epc_byte.c_str(), NULL, 16);
            }
        }

        byte new_epc_array[byte_tag_count];
        for (int i = 0; i < byte_tag_count; i++)
        {
            String new_epc_byte = new_epc.substring(i * 2, i * 2 + 2);
            new_epc_array[i] = (byte)strtol(new_epc_byte.c_str(), NULL, 16);
        }

        byte password_array[byte_password_count];
        for (int i = 0; i < byte_password_count; i++)
        {
            String password_byte = password.substring(i * 2, i * 2 + 2);
            password_array[i] = (byte)strtol(password_byte.c_str(), NULL, 16);
        }

        reader_module.write_tag(current_epc_array, new_epc_array, password_array, current_null);
    }
};
