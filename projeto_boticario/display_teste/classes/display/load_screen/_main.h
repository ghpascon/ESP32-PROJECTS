#include "img.h"

class load_screen_create
{
public:
    void create_load_screen()
    {
        lv_obj_set_style_bg_color(screen_load, lv_color_hex(0x000000), LV_PART_MAIN);
        load_img();
    }
};
