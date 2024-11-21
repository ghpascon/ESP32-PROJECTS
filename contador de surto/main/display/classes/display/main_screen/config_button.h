lv_obj_t *cfg_btn;

void cfg_btn_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		wrong_cfg_password = false;
		cfg_password = "";
		lv_screen_load(screen_config);
	}
}

void cfg_button()
{
	cfg_btn = lv_btn_create(screen_main);
	lv_obj_add_style(cfg_btn, &bt_style, 0);
	lv_obj_align(cfg_btn, LV_ALIGN_CENTER, -110, 90);

	lv_obj_t *label = lv_label_create(cfg_btn);
	lv_label_set_text(label, LV_SYMBOL_SETTINGS);
	lv_obj_center(label);

	lv_obj_add_event_cb(cfg_btn, cfg_btn_click, LV_EVENT_CLICKED, NULL);
}
