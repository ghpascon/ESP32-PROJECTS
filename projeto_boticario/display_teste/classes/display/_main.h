#include "libs.h"
#include "vars.h"
#include "display_setup.h"
#include "screen.h"

class ESP_DISPLAY : private display_setup, private screen
{
public:
    void setup()
    {
        setup_display();
        create_screen();
        lv_screen_load(screen_load);
    }

    void att_display()
    {
        att_screen();

        const int att_display_time = 5;
        static unsigned long current_att_display_time = 0;
        if (millis() - current_att_display_time > att_display_time)
        {
            lv_task_handler();
            lv_tick_inc(att_display_time);
        }
    }
};
