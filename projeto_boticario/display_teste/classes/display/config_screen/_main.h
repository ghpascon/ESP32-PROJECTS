#include "label_main.h"
#include "retry.h"
#include "speed.h"

class config_screen_create
{
public:
    void create_config_screen()
    {
        lv_obj_set_style_bg_color(screen_config, lv_color_hex(0x000000), LV_PART_MAIN);
        label_tunnel();
        speed_selection();
        retry_selection();
    }

    void att_config_screen()
    {
        const int att_time = 300;
        static unsigned long current_att_time = 0;
        if (millis() - current_att_time < att_time)
            return;
        att_speed();
        att_retry();
    }
};
