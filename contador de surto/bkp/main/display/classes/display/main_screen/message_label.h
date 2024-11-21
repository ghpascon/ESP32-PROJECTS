lv_obj_t *label_message;

void message_label()
{
	label_message = lv_label_create(screen_main);
	lv_label_set_text(label_message, "");
	lv_obj_add_style(label_message, &label_style_white_animated, 0);
	lv_obj_align(label_message, LV_ALIGN_CENTER, 0, 90);
	lv_label_set_long_mode(label_message, LV_LABEL_LONG_SCROLL_CIRCULAR);
}

void att_message_label()
{
	static String last_message = "";
	if (device_state == 0)
	{
		if (last_message == display_message)
			return;
		last_message = display_message;
		lv_label_set_text(label_message, String(display_message).c_str());
	}
	else
	{
		last_message = "";
		lv_label_set_text(label_message, String("").c_str());
	}
}