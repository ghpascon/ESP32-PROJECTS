lv_obj_t *label_inspec_ok;

void insp_ok_label()
{
	label_inspec_ok = lv_label_create(screen_inspec);
	lv_label_set_text(label_inspec_ok, "");
	lv_obj_add_style(label_inspec_ok, &label_style, 0);
	lv_obj_align(label_inspec_ok, LV_ALIGN_CENTER, 40, 90);
}

void att_insp_ok_label()
{
	lv_label_set_text(label_inspec_ok, String(wrong_password ? "Senha Incorreta" : ((device_state == 0) ? "Inspec OK!" : "")).c_str());
	lv_obj_set_style_text_color(label_inspec_ok, (wrong_password ? lv_color_hex(0xff0000) : lv_color_hex(0x00ff00)), LV_PART_MAIN);
}