lv_style_t label_title;
lv_style_t label_main;
lv_style_t label_data;

lv_style_t bt_unselected;
lv_style_t bt_selected;
lv_style_t bt_sub_add;

void display_style()
{
    lv_style_init(&label_title);
    lv_style_set_bg_color(&label_title, lv_color_hex(0x000000));
    lv_style_set_text_color(&label_title, lv_color_hex(0xffb41f));
    lv_style_set_text_font(&label_title, &lv_font_montserrat_28);

    lv_style_init(&label_main);
    lv_style_set_bg_color(&label_main, lv_color_hex(0x000000));
    lv_style_set_text_color(&label_main, lv_color_hex(0xffffff));
    lv_style_set_text_font(&label_main, &lv_font_montserrat_26);

    lv_style_init(&label_data);
    lv_style_set_bg_color(&label_data, lv_color_hex(0x000000));
    lv_style_set_text_color(&label_data, lv_color_hex(0xffffff));
    lv_style_set_text_font(&label_data, &lv_font_montserrat_22);

    lv_style_init(&bt_unselected);
    lv_style_set_bg_color(&bt_unselected, lv_color_hex(0xff0000));
    lv_style_set_text_color(&bt_unselected, lv_color_hex(0xffffff));
    lv_style_set_border_color(&bt_unselected, lv_color_hex(0xffffff));
    lv_style_set_border_width(&bt_unselected, 2);
    lv_style_set_shadow_width(&bt_unselected, 0);
    lv_style_set_text_font(&bt_unselected, &lv_font_montserrat_20);
    lv_style_set_radius(&bt_unselected, 10);
    lv_style_set_width(&bt_unselected, LV_SIZE_CONTENT);
    lv_style_set_height(&bt_unselected, LV_SIZE_CONTENT);

    lv_style_init(&bt_selected);
    lv_style_set_bg_color(&bt_selected, lv_color_hex(0x00ff00));
    lv_style_set_text_color(&bt_selected, lv_color_hex(0x000000));
    lv_style_set_border_color(&bt_selected, lv_color_hex(0xffffff));
    lv_style_set_border_width(&bt_selected, 2);
    lv_style_set_shadow_width(&bt_selected, 0);
    lv_style_set_text_font(&bt_selected, &lv_font_montserrat_24);
    lv_style_set_radius(&bt_selected, 10);
    lv_style_set_width(&bt_selected, LV_SIZE_CONTENT);
    lv_style_set_height(&bt_selected, LV_SIZE_CONTENT);

    lv_style_init(&bt_sub_add);
    lv_style_set_bg_color(&bt_sub_add, lv_color_hex(0xffb41f));
    lv_style_set_text_color(&bt_sub_add, lv_color_hex(0x000000));
    lv_style_set_border_color(&bt_sub_add, lv_color_hex(0xffffff));
    lv_style_set_border_width(&bt_sub_add, 2);
    lv_style_set_shadow_width(&bt_sub_add, 0);
    lv_style_set_text_font(&bt_sub_add, &lv_font_montserrat_20);
    lv_style_set_radius(&bt_sub_add, 10);
    lv_style_set_width(&bt_sub_add, LV_SIZE_CONTENT);
    lv_style_set_height(&bt_sub_add, LV_SIZE_CONTENT);
}
