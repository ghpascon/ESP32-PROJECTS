lv_obj_t* time_label;

void config_mode_display() {
  lv_obj_t* config_label;
  config_label = lv_label_create(screen_main);
  lv_label_set_text(config_label, "CONFIG MODE");
  lv_obj_add_style(config_label, &label_yellow, 0);
  lv_obj_set_pos(config_label, 10, 50);

  time_label = lv_label_create(screen_main);
  lv_label_set_text(time_label, "");
  lv_obj_add_style(time_label, &label_style, 0);
  lv_obj_set_pos(time_label, 10, 100);
}

void att_config_status() {
  lv_label_set_text(time_label, ("TEMPO RESTANTE: " + String((reset_config_time - millis()) / 1000)).c_str());
}