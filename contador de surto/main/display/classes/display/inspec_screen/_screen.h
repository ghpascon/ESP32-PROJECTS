#include "inspec_label.h"
#include "inspec_buttons.h"
#include "insp_ok_label.h"
#include "password_label.h"
#include "home_bt.h"

void inspec_screen()
{
	lv_obj_set_style_bg_color(screen_inspec, lv_color_hex(0x000000), LV_PART_MAIN);
	inspec_label();
	inspec_buttons();
	password_label();
	insp_ok_label();
	home_button();
}

void inspec_screen_att()
{
	att_insp_ok_label();
	att_password_label();
}
