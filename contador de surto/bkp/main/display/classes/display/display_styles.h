lv_style_t label_title;
lv_style_t label_emg;
lv_style_t label_emg_back;
lv_style_t label_style;
lv_style_t label_style_white;
lv_style_t label_style_white_animated;
lv_style_t label_red;
lv_style_t label_green;
lv_style_t label_min;
lv_style_t style_circle_red;
lv_style_t style_circle_green;
lv_style_t box_style;
lv_style_t bt_style;

void create_display_styles()
{
	lv_style_init(&label_title);
	lv_style_set_text_color(&label_title, lv_color_hex(0xffff00));
	lv_style_set_text_font(&label_title, &lv_font_montserrat_40);

	lv_style_init(&label_emg);
	lv_style_set_text_color(&label_emg, lv_color_hex(0xffff00));
	lv_style_set_text_font(&label_emg, &lv_font_montserrat_42);

	lv_style_init(&label_emg_back);
	lv_style_set_text_color(&label_emg_back, lv_color_hex(0x000000));
	lv_style_set_text_font(&label_emg_back, &lv_font_montserrat_48);

	lv_style_init(&label_style);
	lv_style_set_text_color(&label_style, lv_color_hex(0x000000));
	lv_style_set_text_font(&label_style, &lv_font_montserrat_26);

	lv_style_init(&label_style_white);
	lv_style_set_text_color(&label_style_white, lv_color_hex(0xffffff));
	lv_style_set_text_font(&label_style_white, &lv_font_montserrat_24);

	lv_style_init(&label_style_white_animated);
	lv_style_set_text_color(&label_style_white_animated, lv_color_hex(0xffffff));
	lv_style_set_text_font(&label_style_white_animated, &lv_font_montserrat_26);
	lv_style_set_width(&label_style_white_animated, 250);
	
	lv_style_init(&label_min);
	lv_style_set_text_color(&label_min, lv_color_hex(0x000000));
	lv_style_set_text_font(&label_min, &lv_font_montserrat_18);

	const int circle_size = 26;
	lv_style_init(&style_circle_red);
	lv_style_set_width(&style_circle_red, circle_size);
	lv_style_set_height(&style_circle_red, circle_size);
	lv_style_set_bg_color(&style_circle_red, lv_color_hex(0xff0000));
	lv_style_set_radius(&style_circle_red, circle_size / 2);
	lv_style_set_border_color(&style_circle_red, lv_color_hex(0x000000));
	lv_style_set_border_width(&style_circle_red, 3);
	lv_style_set_shadow_width(&style_circle_red, 0);
	lv_style_set_outline_width(&style_circle_red, 0);

	lv_style_init(&style_circle_green);
	lv_style_set_width(&style_circle_green, circle_size);
	lv_style_set_height(&style_circle_green, circle_size);
	lv_style_set_bg_color(&style_circle_green, lv_color_hex(0x00ff00));
	lv_style_set_radius(&style_circle_green, circle_size / 2);
	lv_style_set_border_color(&style_circle_green, lv_color_hex(0x000000));
	lv_style_set_border_width(&style_circle_green, 3);
	lv_style_set_shadow_width(&style_circle_green, 0);
	lv_style_set_outline_width(&style_circle_green, 0);

	lv_style_init(&box_style);
	lv_style_set_bg_color(&box_style, lv_color_hex(0xffffff));
	lv_style_set_border_color(&box_style, lv_color_hex(0xffffff));
	lv_style_set_text_color(&box_style, lv_color_hex(0x000000));
	lv_style_set_text_font(&box_style, &lv_font_montserrat_22);
	lv_style_set_border_width(&box_style, 2);
	lv_style_set_radius(&box_style, 10);
	lv_style_set_width(&box_style, 270);
	lv_style_set_height(&box_style, 130);

	lv_style_init(&bt_style);
	lv_style_set_bg_color(&bt_style, lv_color_hex(0xffff00));
	lv_style_set_border_color(&bt_style, lv_color_hex(0xffffff));
	lv_style_set_text_color(&bt_style, lv_color_hex(0x000000));
	lv_style_set_text_font(&bt_style, &lv_font_montserrat_18);
	lv_style_set_border_width(&bt_style, 2);
	lv_style_set_radius(&bt_style, 10);
	lv_style_set_width(&bt_style, LV_SIZE_CONTENT);
	lv_style_set_height(&bt_style, LV_SIZE_CONTENT);
}