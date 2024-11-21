const int max_retry = 10;

lv_obj_t *current_retry;
lv_obj_t *retry_up;
lv_obj_t *retry_down;

void retry_down_click(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (retry > 0)
            Serial2.println("#SET_RETRY:" + String(retry - 1));
    }
}

void retry_up_click(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (retry < max_retry)
            Serial2.println("#SET_RETRY:" + String(retry + 1));
    }
}

void retry_selection()
{
    const int x = 50;
    const int x_offset = 60;
    const int y = 70;

    lv_obj_t *label_retry;
    label_retry = lv_label_create(screen_config);
    lv_label_set_text(label_retry, "RETRY:");
    lv_obj_add_style(label_retry, &label_main, 0);
    lv_obj_align(label_retry, LV_ALIGN_CENTER, 45 - SCREEN_WIDTH / 2, y);

    retry_down = lv_btn_create(screen_config);
    lv_obj_add_style(retry_down, &bt_sub_add, 0);
    lv_obj_align(retry_down, LV_ALIGN_CENTER, x - x_offset, y);
    lv_obj_t *label_retry_down = lv_label_create(retry_down);
    lv_label_set_text(label_retry_down, "-");
    lv_obj_center(label_retry_down);
    lv_obj_add_event_cb(retry_down, retry_down_click, LV_EVENT_CLICKED, NULL);

    current_retry = lv_label_create(screen_config);
    lv_label_set_text(current_retry, "");
    lv_obj_add_style(current_retry, &label_data, 0);
    lv_obj_align(current_retry, LV_ALIGN_CENTER, x, y);

    retry_up = lv_btn_create(screen_config);
    lv_obj_add_style(retry_up, &bt_sub_add, 0);
    lv_obj_align(retry_up, LV_ALIGN_CENTER, x + x_offset, y);
    lv_obj_t *label_retry_up = lv_label_create(retry_up);
    lv_label_set_text(label_retry_up, "+");
    lv_obj_center(label_retry_up);
    lv_obj_add_event_cb(retry_up, retry_up_click, LV_EVENT_CLICKED, NULL);
}

void att_retry()
{
    lv_label_set_text(current_retry, String(retry).c_str());
}