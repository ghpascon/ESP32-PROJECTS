lv_obj_t *cfg_label_password;

void cfg_password_label()
{
	cfg_label_password = lv_label_create(screen_config);
	lv_label_set_text(cfg_label_password, "");
	lv_obj_add_style(cfg_label_password, &label_style_white, 0);
	lv_obj_align(cfg_label_password, LV_ALIGN_CENTER, 0, 60);
}

void att_cfg_password_label()
{
	lv_label_set_text(cfg_label_password, String("Senha: " + cfg_password).c_str());
}
