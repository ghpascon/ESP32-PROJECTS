lv_obj_t *label_password;

void password_label()
{
	label_password = lv_label_create(screen_inspec);
	lv_label_set_text(label_password, "");
	lv_obj_add_style(label_password, &label_style_white, 0);
	lv_obj_align(label_password, LV_ALIGN_CENTER, 0, 60);
}

void att_password_label()
{
	lv_label_set_text(label_password, String("Senha: " + password).c_str());
}
