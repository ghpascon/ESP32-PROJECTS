void label_tunnel()
{
    lv_obj_t *title;
    title = lv_label_create(screen_config);
    lv_label_set_text(title, "RFID SMART TUNNEL");
    lv_obj_add_style(title, &label_title, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 30 - SCREEN_HEIGHT / 2);
}
