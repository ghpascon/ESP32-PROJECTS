void surge_version_label() {
  lv_obj_t* surge_label;
  surge_label = lv_label_create(screen_main);
  lv_label_set_text(surge_label, "STATUS DA API?");
  lv_obj_add_style(surge_label, &label_min_style, 0);
  lv_obj_align(surge_label, LV_ALIGN_CENTER, 0, SCREEN_HEIGHT / 2 - 20);
}
