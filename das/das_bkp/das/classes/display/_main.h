#include "vars.h"
#include "screens.h"
#include "check.h"

class LCM_DISPLAY : private check_display
{
public:
    void setup()
    {
        Lcm.begin();
        Lcm.changeBacklight(100);
    }

    void check()
    {
        check_mode();
        check_retry();
        check_speed();
        check_cfg();
        check_password();
        check_ant_cfg();
    }

    void send_data()
    {
        const int send_time = 5000;
        static unsigned long current_send_time = 0;
        if (millis() - current_send_time < send_time)
            return;
        current_send_time = millis();

        retry_display.write(retry);
        speed_display.write(speed);
        mode_1_ant_power_label.write(ant_cfg[0][0]);
        mode_1_ant_rssi_label.write(ant_cfg[0][1]);
        mode_2_ant_power_label.write(ant_cfg[1][0]);
        mode_2_ant_rssi_label.write(ant_cfg[1][1]);
        mode_3_ant_power_label.write(ant_cfg[2][0]);
        mode_3_ant_rssi_label.write(ant_cfg[2][1]);
        mode_4_ant_power_label.write(ant_cfg[3][0]);
        mode_4_ant_rssi_label.write(ant_cfg[3][1]);
    }

    void load_screen_on_start()
    {
        const int load_time = 5000;
        static bool loaded = false;
        if (loaded)
            return;

        Lcm.changePicId(load_screen);

        if (millis() > load_time)
        {
            Lcm.changePicId(mode);
            loaded = true;
        }
    }

    void post_cfg()
    {
        String to_post = "";
        static byte last_mode = 0;

        if (posted || !connected)
            return;

        if (last_mode == mode)
            return;

        last_mode = mode;

        if (mode >= 3 && mode <= 6)
        {
            String cmd;
            for (int i = 0; i < device_num; i++)
            {
                if (i == mode -3)
                    cmd = commands[0];
                else
                    cmd = commands[1];

                to_post += "{\"command\":\""+cmd+"\",\"device\":{\"name\":\"" + device[i] + "\"}}@";
            }
        }

        esp_post.post(to_post);
    }
};
