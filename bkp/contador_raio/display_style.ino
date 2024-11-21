void display_style() {
  lv_style_init(&label_style);
  lv_style_set_bg_color(&label_style, lv_color_hex(0x000000));
  lv_style_set_text_color(&label_style, lv_color_hex(0xffffff));
  lv_style_set_text_font(&label_style, &lv_font_montserrat_24);

  lv_style_init(&label_min_style);
  lv_style_set_bg_color(&label_min_style, lv_color_hex(0x000000));
  lv_style_set_text_color(&label_min_style, lv_color_hex(0xffffff));
  lv_style_set_text_font(&label_min_style, &lv_font_montserrat_20);

  lv_style_init(&label_green);
  lv_style_set_bg_color(&label_green, lv_color_hex(0x000000));
  lv_style_set_text_color(&label_green, lv_color_hex(0x00ff00));
  lv_style_set_text_font(&label_green, &lv_font_montserrat_26);

  lv_style_init(&label_yellow);
  lv_style_set_bg_color(&label_yellow, lv_color_hex(0x000000));
  lv_style_set_text_color(&label_yellow, lv_color_hex(0xffff00));
  lv_style_set_text_font(&label_yellow, &lv_font_montserrat_26);

  lv_style_init(&label_red);
  lv_style_set_bg_color(&label_red, lv_color_hex(0x000000));
  lv_style_set_text_color(&label_red, lv_color_hex(0xff0000));
  lv_style_set_text_font(&label_red, &lv_font_montserrat_24);
}
