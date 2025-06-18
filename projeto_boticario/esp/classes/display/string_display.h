class string_display
{
public:
    void set_msg()
    {
        set_state();
        zera_box_infos();
        box_not_inserted();
        set_instruction_label();
        set_state_icon();
        set_status_label();
    }

private:
    void set_state()
    {
        if (debug_mode)
            return;

        static bool finished = false;

        if (emg)
            step = 0;

        else if (cx_ok)
        {
            step = 6;
            finished = false;
        }
        else if (cx_erro)
        {
            step = 7;
            finished = false;
        }
        else if (!box_inside)
        {
            step = 2;
            finished = true;
        }
        else
        {
            step = 5;
        }
    }

    void zera_box_infos()
    {
        const int timeout = 20000;
        static unsigned long current_time = 0;

        if (step != 2)
            current_time = millis();

        if (millis() - current_time < timeout)
            return;

    }

    void box_not_inserted()
    {
        const int timeout = 20000;
        static unsigned long current_time = 0;
        if (step != 3 && step != 4)
            current_time = millis();

        if (millis() - current_time < timeout)
            return;

        step = 2;
    }

    void set_instruction_label()
    {
        static byte last_step = 99;
        if (last_step == step)
            return;
        last_step = step;

        String instruction_label_msg = instruction_messages[step];
        if (step == 6 || step == 7)
            instruction_label_msg += "\n" + state_msg;

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


    void set_status_label()
    {
        static String last_status_msg = "";

        if (last_status_msg == status_msg)
            return;

        last_status_msg = status_msg;

        static const String sep = "SENSOR_IN";
        String status_1 = status_msg.substring(0, status_msg.indexOf(sep));
        String status_2 = status_msg.substring(status_msg.indexOf(sep));

        display_status_label.write(status_1);
        display_status_label_2.write(status_2);
    }
};
