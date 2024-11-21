#include "main_title.h"
#include "device_state.h"
#include "online_status.h"
#include "api_status.h"
#include "total_surge.h"
#include "version.h"
#include "insp_button.h"
#include "message_label.h"
#include "config_button.h"

void main_screen()
{
	lv_obj_set_style_bg_color(screen_main, lv_color_hex(0x000000), LV_PART_MAIN);
	main_title();
	device_state_window();
	online_status_label();
	api_status_label();
	total_surge_label();
	version_label();
	insp_button();
	message_label();
	cfg_button();
}

void main_screen_att()
{
	att_device_state_status();
	att_online_status();
	att_api_status();
	att_total_surge_status();
	att_insp_button();
	att_message_label();
}


