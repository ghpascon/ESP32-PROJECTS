#include "vars.h"
#include "modes.h"

class MOTOR_STATE : private modes
{
public:
    void functions()
    {
        check_box_inside();
        check_box_out();
        check_sensors();
        check_box_state();
        check_door_sensors();
        check_error();
        timeout_motor_off();
    }

private:
    void check_box_inside()
    {
        if (box_num == "" || box_qtd < 1)
            return;

        const int time = 500;
        static unsigned long current_time = 0;
        if (box_inside)
            current_time = millis();

        if (millis() - current_time < time)
            return;

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
        if (door_mode == 1)
            door_mode_1();
        else if (door_mode == 2)
            door_mode_2();
        else if (door_mode == 3)
            door_mode_3();

        reprove();

        if (box_num == "" || box_qtd < 1)
        {
            turn_all_off();
        }
    }

    void check_box_state()
    {
        if (cx_ok)
        {
            motor = true;
            motor_reverse = false;
            cx_erro = false;
            read_on = false;
            readed = true;
            waiting_answer = false;
        }
        if (cx_erro)
        {
            motor = true;
            motor_reverse = true;
            cx_ok = false;
            read_on = false;
            readed = true;
            waiting_answer = false;
        }
    }

    void check_door_sensors()
    {
        const int time = 1000;
        static unsigned long current_time = 0;
        bool aux_motor = false;

        if (!p1_open && !p1_close && !p2_open && !p2_close)
            readed = false;

        if (!cx_erro && !cx_ok)
            return;

        if (cx_ok)
        {
            aux_motor = !motor_reverse && !p2_close && !p2_open;
        }
        else if (cx_erro)
        {
            aux_motor = motor_reverse && !p1_close && !p1_open;
        }

        if (!aux_motor)
            current_time = millis();

        motor = (millis() - current_time > time);
    }

    bool close_door_step()
    {
        return ((step == 3 || step == 4));
    }
    void check_error()
    {
        if (emg)
        {
            turn_all_off();
            box_off();
            box_inside = true;
            cx_erro = true;
        }

        if (sensor_in && sensor_out)
        {
            turn_all_off();
        }

        static const int timeout_motor = answer_timeout;
        static unsigned long current_timeout_motor = 0;
        
        static const int timeout_state = 7000;
        static unsigned long current_timeout_state = 0;

        if (!box_inside || motor || readed || close_door_step())
            current_timeout_motor = millis();

        if (millis() - current_timeout_motor > timeout_motor)
        {
            cx_erro = true;
            timeout = true;
        }

        if ((!cx_erro && !cx_ok) || !motor)
            current_timeout_state = millis();

        if (millis() - current_timeout_state > timeout_state)
        {
            turn_all_off();
            box_off();
        }

        const int timeout_motor_on = 7000;
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

        const int waiting_timeout = 5000;
        static unsigned long current_waiting_answer = millis();

        if (!waiting_answer)
            current_waiting_answer = millis();
        if (millis() - current_waiting_answer > waiting_timeout)
        {
            cx_erro = true;
            timeout = true;
        }
    }

private:
    void box_off()
    {
        box_inside = false;
        cx_ok = false;
        cx_erro = false;
        turn_off = false;
        box_num = "";
        box_qtd = 0;
        timeout = false;
        waiting_answer = false;
    }

    void turn_all_off()
    {
        motor = false;
        motor_reverse = false;
        read_on = false;
        waiting_answer = false;
    }

    void timeout_motor_off()
    {
        const long motor_off_time = 1200000;
        static unsigned long current_motor_off_time = 0;
        if (motor)
            current_motor_off_time = millis();
        if (millis() - current_motor_off_time > motor_off_time)
            ESP.restart();
    }
};
