void main_title()
{
	lv_obj_t *title;
	title = lv_label_create(screen_main);
	lv_label_set_text(title, "EMBRASTEC");
	lv_obj_add_style(title, &label_title, 0);
	lv_obj_align(title, LV_ALIGN_CENTER, 0, -95);
}