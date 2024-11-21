#include "style.h"
#include "screens_setup.h"
#include "load_screen/_main.h"
#include "config_screen/_main.h"

class screen : private load_screen_create, private config_screen_create
{
public:
    void create_screen()
    {
        display_style();
        screens_setup();

        create_load_screen();
        create_config_screen();
    }

    void att_screen()
    {
        change_screen();
        att_config_screen();
    }

private:
    void change_screen()
    {
        static bool loaded = false;
        if (loaded || millis() < 5000)
            return;
        lv_screen_load(screen_config);
        loaded = true;
    }
};
