void lv_create_main_gui() {
  display_style();
  screens_setup();

  //screen_main
  (config_mode) ? config_mode_display() : on_mode_display();
  surge_version_label();
}

void screens_setup() {
  screen_main = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen_main, lv_color_hex(0x000000), LV_PART_MAIN);

  screen_manut = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(screen_manut, lv_color_hex(0x000000), LV_PART_MAIN);
}

void att_screen() {
  const int att_time = 300;
  static unsigned long current_att_time = 0;
  if (millis() - current_att_time < att_time) return;
  (config_mode) ? att_config_status() : att_online_status();
}

