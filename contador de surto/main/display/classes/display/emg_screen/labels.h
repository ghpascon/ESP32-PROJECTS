void emg_labels()
{
	lv_obj_t *label_1;
	label_1 = lv_label_create(screen_emg);
	lv_label_set_text(label_1, "Verificar o");
	lv_obj_add_style(label_1, &label_title, 0);
	lv_obj_set_style_text_color(label_1, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_align(label_1, LV_ALIGN_CENTER, 0, -35);

	lv_obj_t *label_2;
	label_2 = lv_label_create(screen_emg);
	lv_label_set_text(label_2, "DPS");
	lv_obj_add_style(label_2, &label_title, 0);
	lv_obj_set_style_text_color(label_2, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_align(label_2, LV_ALIGN_CENTER, 0, 10);

	lv_obj_t *label_3;
	label_3 = lv_label_create(screen_emg);
	lv_label_set_text(label_3, LV_SYMBOL_WARNING);
	lv_obj_add_style(label_3, &label_emg_back, 0);
	lv_obj_align(label_3, LV_ALIGN_CENTER, 0, 60);

	lv_obj_t *label_4;
	label_4 = lv_label_create(screen_emg);
	lv_label_set_text(label_4, LV_SYMBOL_WARNING);
	lv_obj_add_style(label_4, &label_emg, 0);
	lv_obj_align(label_4, LV_ALIGN_CENTER, 0, 60);
}

