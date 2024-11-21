#include "cfg_buttons.h"
#include "cfg_home_bt.h"
#include "cfg_insp_ok_label.h"
#include "cfg_label.h"
#include "cfg_password_label.h"

void cgf_screen()
{
	lv_obj_set_style_bg_color(screen_config, lv_color_hex(0x000000), LV_PART_MAIN);
	config_label();
	config_buttons();
	cfg_password_label();
	cfg_insp_ok_label();
	cfg_home_button();
}

void config_screen_att()
{
	att_cfg_insp_ok_label();
	att_cfg_password_label();
}
