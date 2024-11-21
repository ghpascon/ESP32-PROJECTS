const int max_speed = 4;

lv_obj_t *current_speed;
lv_obj_t *speed_up;
lv_obj_t *speed_down;

void speed_down_click(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (speed > 1)
            Serial2.println("#SET_SPEED:" + String(speed - 1));
    }
}

void speed_up_click(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (speed < max_speed)
            Serial2.println("#SET_SPEED:" + String(speed + 1));
    }
}

void speed_selection()
{
    const int x = 50;
    const int x_offset = 60;
    const int y = -20;

    lv_obj_t *label_speed;
    label_speed = lv_label_create(screen_config);
    lv_label_set_text(label_speed, "SPEED:");
    lv_obj_add_style(label_speed, &label_main, 0);
    lv_obj_align(label_speed, LV_ALIGN_CENTER, 60 - SCREEN_WIDTH / 2, y);

    speed_down = lv_btn_create(screen_config);
    lv_obj_add_style(speed_down, &bt_sub_add, 0);
    lv_obj_align(speed_down, LV_ALIGN_CENTER, x - x_offset, y);
    lv_obj_t *label_speed_down = lv_label_create(speed_down);
    lv_label_set_text(label_speed_down, "-");
    lv_obj_center(label_speed_down);
    lv_obj_add_event_cb(speed_down, speed_down_click, LV_EVENT_CLICKED, NULL);

    current_speed = lv_label_create(screen_config);
    lv_label_set_text(current_speed, "");
    lv_obj_add_style(current_speed, &label_data, 0);
    lv_obj_align(current_speed, LV_ALIGN_CENTER, x, y);

    speed_up = lv_btn_create(screen_config);
    lv_obj_add_style(speed_up, &bt_sub_add, 0);
    lv_obj_align(speed_up, LV_ALIGN_CENTER, x + x_offset, y);
    lv_obj_t *label_speed_up = lv_label_create(speed_up);
    lv_label_set_text(label_speed_up, "+");
    lv_obj_center(label_speed_up);
    lv_obj_add_event_cb(speed_up, speed_up_click, LV_EVENT_CLICKED, NULL);
}

void att_speed()
{
    if (speed == 1)
        lv_label_set_text(current_speed, "25%");
    if (speed == 2)
        lv_label_set_text(current_speed, "50%");
    if (speed == 3)
        lv_label_set_text(current_speed, "75%");
    if (speed == 4)
        lv_label_set_text(current_speed, "100%");
}