void inspec_label()
{
	lv_obj_t *inspec_1;
	inspec_1 = lv_label_create(screen_inspec);
	lv_label_set_text(inspec_1, "Digite a Senha Para");
	lv_obj_add_style(inspec_1, &label_style_white, 0);
	lv_obj_align(inspec_1, LV_ALIGN_CENTER, 0, -100);

	lv_obj_t *inspec_2;
	inspec_2 = lv_label_create(screen_inspec);
	lv_label_set_text(inspec_2, " Confirmar a Inspec");
	lv_obj_add_style(inspec_2, &label_style_white, 0);
	lv_obj_align(inspec_2, LV_ALIGN_CENTER, 0, -70);
}
