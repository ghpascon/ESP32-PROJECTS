#include "vars.h"

class MOTOR_STATE
{
public:
    void functions()
    {
        check_box_inside();
        check_box_out();
        check_sensors();
        check_box_state();
        check_error();
        timeout_motor_off();
    }

    void check_box_inside()
    {
        if (sensor_in)
        {
            box_inside = true;
        }
    }

    void check_box_out()
    {
        const int time_turn_off = 1000;
        static unsigned long current_time_turn_off = 0;

        static bool last_sensor_in = false;
        static bool last_sensor_out = false;

        if (!box_inside)
            return;

        if (cx_erro && last_sensor_in != sensor_in && !sensor_in)
        {
            turn_off = true;
        }
        if (cx_ok && last_sensor_out != sensor_out && !sensor_out)
        {
            turn_off = true;
        }

        if (!turn_off)
            current_time_turn_off = millis();

        if (millis() - current_time_turn_off > time_turn_off)
        {
            box_off();
            turn_all_off();
        }
        last_sensor_in = sensor_in;
        last_sensor_out = sensor_out;
    }

    void check_sensors()
    {
        if (!box_inside || cx_ok || cx_erro)
        {
            current_retry_cnt = 0;
            return;
        }

        motor = true;

        if (sensor_out && !motor_reverse)
            current_retry_cnt++;

        if (current_retry_cnt > retry_cnt)
        {
            turn_all_off();
            if (!integrated)
                cx_ok = true;
            return;
        }

        motor_reverse = sensor_out;

        read_on = motor;
    }

    void check_box_state()
    {
        if (cx_ok)
        {
            motor = true;
            motor_reverse = false;
            cx_erro = false;
            read_on = false;
        }
        if (cx_erro)
        {
            motor = true;
            motor_reverse = true;
            cx_ok = false;
            read_on = false;
        }
    }

    void check_error()
    {
        if (emg)
        {
            turn_all_off();
            box_off();
            cx_erro = true;
        }

        if (sensor_in && sensor_out)
        {
            turn_all_off();
        }

        const int timeout_motor = 5000;
        static unsigned long current_timeout_motor = 0;
        const int timeout_state = 5000;
        static unsigned long current_timeout_state = 0;

        if (!box_inside)
            current_timeout_motor = millis();
        else
        {
            if (motor || emg)
            {
                current_timeout_motor = millis();
            }
        }

        if (millis() - current_timeout_motor > current_timeout_motor)
        {
            cx_erro = true;
        }

        if ((!cx_erro && !cx_ok) || !motor)
            current_timeout_state = millis();

        if (millis() - current_timeout_state > timeout_state)
        {
            turn_all_off();
            box_off();
        }

        const int timeout_motor_on = 5000;
        static unsigned long current_timeout_motor_on = 0;
        if (!motor)
            current_timeout_motor_on = millis();
        if (motor && (sensor_in || sensor_out))
            current_timeout_motor_on = millis();

        if (millis() - timeout_motor_on > current_timeout_motor_on)
        {
            turn_all_off();
            box_off();
        }
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

    void timeout_motor_off()
    {
        const int motor_off_time = 1200000;
        static unsigned long current_motor_off_time = 0;
        if (motor)
            current_motor_off_time = millis();
        if (millis() - current_motor_off_time > motor_off_time)
            ESP.restart();
    }
};
