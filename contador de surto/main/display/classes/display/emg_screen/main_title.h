void main_emg_title()
{
	lv_obj_t *title;
	title = lv_label_create(screen_emg);
	lv_label_set_text(title, "EMBRASTEC");
	lv_obj_add_style(title, &label_title, 0);
	lv_obj_set_style_text_color(title, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_align(title, LV_ALIGN_CENTER, 0, -95);
}