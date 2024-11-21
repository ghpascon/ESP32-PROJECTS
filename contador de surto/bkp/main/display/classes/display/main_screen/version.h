lv_obj_t *label_version;

void version_label()
{
	label_version = lv_label_create(device_state_obj);
	lv_label_set_text(label_version, "Surge Counter V: 1.0");
	lv_obj_add_style(label_version, &label_min, 0);
	lv_obj_align(label_version, LV_ALIGN_CENTER, 0, 45);
}
