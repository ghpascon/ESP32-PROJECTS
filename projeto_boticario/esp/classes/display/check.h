#include "metrics.h"

class check_display : public metrics
{
public:
    void check()
    {
        check_mode();
        check_retry();
        check_speed();
        check_cfg_bt();
    }

private:
    void check_mode()
    {
        if (mode_buttons.available())
        {
            int value = mode_buttons.getData();

            mode = value;
            Serial.println("Mode: " + String(mode));
            Serial1.println("#PERFIL:" + String(mode - 2));
            Lcm.changePicId(mode);
        }
    }


    void check_retry()
    {
        if (retry_buttons.available())
        {
            int value = retry_buttons.getData();

            if (retry > retry_interval[1])
                retry = 0;

            if (value == 0)
            {
                if (retry > retry_interval[0])
                    retry--;
            }
            if (value == 1)
            {
                if (retry < retry_interval[1])
                    retry++;
            }
            Serial.println("Retry: " + String(retry));
            retry_display.write(retry);
        }
    }

    void check_speed()
    {
        if (speed_buttons.available())
        {
            int value = speed_buttons.getData();

            if (value == 0)
            {
                if (speed > speed_interval[0])
                    speed--;
            }
            if (value == 1)
            {
                if (speed < speed_interval[1])
                    speed++;
            }
            Serial.println("Speed: " + String(speed));
            speed_display.write(speed);
        }
    }

    void check_cfg_bt()
    {
        if (cfg_button.available())
        {
            int value = cfg_button.getData();

            if (value == 0)
            {
                Lcm.changePicId(op_screen);
            }
            else if (value == 1)
            {
                Lcm.changePicId(mode);
            }
            else if (value == 2)
            {
                Lcm.changePicId(status_screen);
            }
            else if (value == 3)
            {
                clear_metrics();
            }
        }
    }
};
