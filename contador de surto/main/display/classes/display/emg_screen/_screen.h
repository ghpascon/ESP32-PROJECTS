#include "main_title.h"
#include "check_device_state.h"
#include "labels.h"

void emg_screen()
{
	lv_obj_set_style_bg_color(screen_emg, lv_color_hex(0xff0000), LV_PART_MAIN);
	main_emg_title();
	emg_labels();
}

void emg_screen_att()
{
	check_device_state();
}


