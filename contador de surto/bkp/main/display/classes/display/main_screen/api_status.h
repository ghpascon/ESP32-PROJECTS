lv_obj_t *label_api;

void api_status_label()
{
	label_api = lv_label_create(device_state_obj);
	lv_label_set_text(label_api, "---");
	lv_obj_add_style(label_api, &label_style, 0);
	lv_obj_align(label_api, LV_ALIGN_CENTER, 0, -15);
}

void att_api_status()
{
	lv_label_set_text(label_api, String("Operacional: " + api_status).c_str());
}