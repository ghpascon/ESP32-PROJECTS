void config_label()
{
	lv_obj_t *config_1;
	config_1 = lv_label_create(screen_config);
	lv_label_set_text(config_1, "Digite a Senha");
	lv_obj_add_style(config_1, &label_style_white, 0);
	lv_obj_align(config_1, LV_ALIGN_CENTER, 0, -100);

	lv_obj_t *config_2;
	config_2 = lv_label_create(screen_config);
	lv_label_set_text(config_2, "para ajustes");
	lv_obj_add_style(config_2, &label_style_white, 0);
	lv_obj_align(config_2, LV_ALIGN_CENTER, 0, -70);
}
