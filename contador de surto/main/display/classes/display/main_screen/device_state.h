void device_state_window()
{
	device_state_obj = lv_obj_create(screen_main);
	lv_obj_clear_flag(device_state_obj, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_style(device_state_obj, &box_style, 0);
	lv_obj_align(device_state_obj, LV_ALIGN_CENTER, 0, -5);
}

void att_device_state_status()
{
	switch (device_state)
	{
	case 0:
		lv_obj_set_style_bg_color(device_state_obj, lv_color_hex(0x00ff00), LV_PART_MAIN);
		break;

	case 1:
		lv_obj_set_style_bg_color(device_state_obj, lv_color_hex(0xffff00), LV_PART_MAIN);
		break;

	case 2:
		lv_obj_set_style_bg_color(device_state_obj, lv_color_hex(0xff0000), LV_PART_MAIN);
		break;

	default:
		device_state = 0;
		break;
	}
}