lv_obj_t *insp_btn;

void insp_btn_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		wrong_password = false;
		password = "";
		lv_screen_load(screen_inspec);
	}
}

void insp_button()
{
	insp_btn = lv_btn_create(screen_main);
	lv_obj_add_style(insp_btn, &bt_style, 0);

	lv_obj_t *label = lv_label_create(insp_btn);
	lv_label_set_text(label, "Realizar Inspec");
	lv_obj_center(label);

	lv_obj_add_event_cb(insp_btn, insp_btn_click, LV_EVENT_CLICKED, NULL);
}

void att_insp_button()
{
	static int last_device_state = 999;
	if (last_device_state == device_state)
		return;
	last_device_state = device_state;

	(device_state == 0)
		? lv_obj_align(insp_btn, LV_ALIGN_CENTER, 500, 500)
		: lv_obj_align(insp_btn, LV_ALIGN_CENTER, 0, 90);
}