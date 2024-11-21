lv_obj_t *label_status;
lv_obj_t *circle_sts;

void online_status_label()
{
	label_status = lv_label_create(device_state_obj);
	lv_label_set_text(label_status, "---");
	lv_obj_add_style(label_status, &label_style, 0);
	lv_obj_align(label_status, LV_ALIGN_CENTER, 0, -45);

	circle_sts = lv_obj_create(device_state_obj);
	lv_obj_clear_flag(circle_sts, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_add_style(circle_sts, &style_circle_red, 0);
	lv_obj_add_style(circle_sts, &style_circle_green, LV_STATE_CHECKED);
	lv_obj_align(circle_sts, LV_ALIGN_CENTER, 80, -45);
}

void att_online_status()
{
	lv_label_set_text(label_status,  String(online ? "Online" : "Offline").c_str());
	online ? lv_obj_add_state(circle_sts, LV_STATE_CHECKED) : lv_obj_clear_state(circle_sts, LV_STATE_CHECKED);
}