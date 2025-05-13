class modes
{
public:
    void door_mode_1()
    {
        if (!box_inside || cx_ok || cx_erro)
        {
            current_retry_cnt = 0;
            return;
        }

        bool mode_door = !p1_close && !p1_open && !p2_close && !p2_open;
        motor = mode_door;

        if (sensor_out && !motor_reverse && current_retry_cnt <= retry)
        {
            Serial.println("#CURRENT_RETRY:" + String(current_retry_cnt) + "|" + String(retry));
            Serial1.println("#CURRENT_RETRY:" + String(current_retry_cnt) + "|" + String(retry));
            current_retry_cnt++;
        }

        if (current_retry_cnt > retry)
        {
            turn_all_off();
            readed = true;
            if (!integrated)
                cx_ok = true;
            return;
        }

        motor_reverse = sensor_out;

        read_on = mode_door;
    }

    void door_mode_2()
    {
        if (!box_inside || cx_ok || cx_erro)
        {
            current_retry_cnt = 0;
            return;
        }

        bool mode_door = p1_close && p1_open && !p2_close && !p2_open;
        motor = mode_door || sensor_in;

        if (sensor_out && !motor_reverse && current_retry_cnt <= retry)
        {
            Serial1.println("#CURRENT_RETRY:" + String(current_retry_cnt) + "|" + String(retry));
            current_retry_cnt++;
        }

        if (current_retry_cnt > retry)
        {
            turn_all_off();
            readed = true;
            if (!integrated)
                cx_ok = true;
            return;
        }

        motor_reverse = sensor_out;

        read_on = mode_door;
    }

    void door_mode_3()
    {
        if (!box_inside || cx_ok || cx_erro)
        {
            current_retry_cnt = 0;
            return;
        }

        bool mode_door = p1_close && p1_open && p2_close && p2_open;
        motor = mode_door || sensor_in;

        if (sensor_out && !motor_reverse && current_retry_cnt <= retry)
        {
            Serial1.println("#CURRENT_RETRY:" + String(current_retry_cnt) + "|" + String(retry));
            current_retry_cnt++;
        }

        if (current_retry_cnt > retry)
        {
            turn_all_off();
            readed = true;

            if (!integrated)
                cx_ok = true;
            return;
        }

        motor_reverse = sensor_out;

        read_on = mode_door;
    }

    void reprove()
    {
        static const int time = answer_timeout;
        static unsigned long current_time = 0;

        if (current_retry_cnt <= retry)
            current_time = millis();

        if (millis() - current_time < time)
            return;

        cx_erro = true;
        timeout = true;
    }

private:
    void box_off()
    {
        box_inside = false;
        cx_ok = false;
        cx_erro = false;
        turn_off = false;
    }

    void turn_all_off()
    {
        motor = false;
        motor_reverse = false;
        read_on = false;
    }
};