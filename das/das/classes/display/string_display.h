class string_display
{
public:
    void set_msg()
    {
        set_state();
        set_instruction_label();
        set_state_icon();
        set_box_label();
    }

private:
    void set_state()
    {
        if (emg)
            step = 0;
        else if (box_num == "")
            step = 1;

        else if (cx_ok)
            step = 6;
        else if (cx_erro)
            step = 7;

        else if (!box_inside)
            step = 2;
        else if (!read_on)
        {
            if (door_mode == 2)
                step = 3;
            else if (door_mode == 3)
                step = 4;
        }
        else if (read_on)
        {
            step = 5;
        }
    }

    void set_instruction_label()
    {
        static byte last_step = 99;
        if (last_step == step)
            return;
        last_step = step;
        String instruction_label_msg = instruction_messages[step];
        display_instruction_label.write(instruction_label_msg);
    }

    void set_state_icon()
    {
        const int change_time = 500;
        static unsigned long current_change_time = 0;
        static byte icon_step = 1;
        if (millis() - current_change_time < change_time)
            return;

        current_change_time = millis();

        byte state_icon_step = step + 1;
        byte interval = (state_icon_step - 1) * 3;

        icon_step++;
        if (icon_step > 3)
            icon_step = 1;

        state_icon.write(state_icon_step == 0 ? 0 : icon_step + interval);
    }

    void set_box_label()
    {
        static String last_box_num = "";
        if (last_box_num == box_num + String(box_qtd))
            return;
        last_box_num = box_num + String(box_qtd);
        String box_label = "BOX NUMBER:\n" + String(box_num) + "\nQTD: " + String(box_qtd);
        display_box_label.write(box_label);
    }
};
