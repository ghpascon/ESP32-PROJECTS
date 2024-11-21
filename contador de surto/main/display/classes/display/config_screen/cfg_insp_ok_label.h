lv_obj_t *cfg_label_inspec_ok;

void cfg_insp_ok_label()
{
	cfg_label_inspec_ok = lv_label_create(screen_config);
	lv_label_set_text(cfg_label_inspec_ok, "");
	lv_obj_add_style(cfg_label_inspec_ok, &label_style, 0);
	lv_obj_align(cfg_label_inspec_ok, LV_ALIGN_CENTER, 40, 90);
}

void att_cfg_insp_ok_label()
{
	lv_label_set_text(cfg_label_inspec_ok, String(wrong_cfg_password ? "Senha Incorreta" : ((cfg_password_ok) ? "Raios Zerados" : "")).c_str());
	lv_obj_set_style_text_color(cfg_label_inspec_ok, (wrong_cfg_password ? lv_color_hex(0xff0000) : lv_color_hex(0x00ff00)), LV_PART_MAIN);
}