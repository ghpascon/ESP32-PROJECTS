lv_obj_t* online_label;
lv_obj_t* response_label;
lv_obj_t* surtos_label;

void on_mode_display() {
  online_label = lv_label_create(screen_main);
  lv_label_set_text(online_label, "");
  lv_obj_add_style(online_label, &label_red, 0);
  lv_obj_add_style(online_label, &label_green, LV_STATE_CHECKED);
  lv_obj_set_pos(online_label, 10, 50);

  lv_obj_t* api_label;
  api_label = lv_label_create(screen_main);
  lv_label_set_text(api_label, "STATUS DA API?");
  lv_obj_add_style(api_label, &label_style, 0);
  lv_obj_set_pos(api_label, 10, 90);

  response_label = lv_label_create(screen_main);
  lv_label_set_text(response_label, "");
  lv_obj_add_style(response_label, &label_style, 0);
  lv_obj_set_pos(response_label, 10, 120);

  surtos_label = lv_label_create(screen_main);
  lv_label_set_text(surtos_label, "");
  lv_obj_add_style(surtos_label, &label_style, 0);
  lv_obj_set_pos(surtos_label, 10, 160);
}

void att_online_status() {
  lv_label_set_text(online_label, connected ? "ONLINE" : "OFFLINE");
  connected ? lv_obj_add_state(online_label, LV_STATE_CHECKED) : lv_obj_clear_state(online_label, LV_STATE_CHECKED);

  lv_label_set_text(response_label, display_post_response.c_str());

  lv_label_set_text(surtos_label, ("TOTAL DE SURTOS: " + String(total_lightning)).c_str());
}