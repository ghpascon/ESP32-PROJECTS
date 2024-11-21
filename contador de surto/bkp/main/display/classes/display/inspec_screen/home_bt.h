lv_obj_t *bt_home;

void bt_home_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		lv_screen_load(screen_main);
	}
}

void home_button()
{
	bt_home = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_home, &bt_style, 0);
	lv_obj_align(bt_home, LV_ALIGN_CENTER, -110, 90);
	lv_obj_t *label_bt_home = lv_label_create(bt_home);
	lv_label_set_text(label_bt_home, LV_SYMBOL_HOME);
	lv_obj_center(label_bt_home);
	lv_obj_add_event_cb(bt_home, bt_home_click, LV_EVENT_CLICKED, NULL);
}

