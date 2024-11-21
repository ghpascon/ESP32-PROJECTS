lv_obj_t *cfg_bt_0;
lv_obj_t *cfg_bt_1;
lv_obj_t *cfg_bt_2;
lv_obj_t *cfg_bt_3;
lv_obj_t *cfg_bt_4;
lv_obj_t *cfg_bt_5;
lv_obj_t *cfg_bt_6;
lv_obj_t *cfg_bt_7;
lv_obj_t *cfg_bt_8;
lv_obj_t *cfg_bt_9;

void check_cfg_ok()
{

	if (cfg_password.length() < zera_raio.length())
		return;

	cfg_password = cfg_password.substring(0, zera_raio.length());

	if (cfg_password == zera_raio)
	{
		cfg_password_ok = true;
		wrong_cfg_password = false;
	}
	else
		wrong_cfg_password = true;

	cfg_password = "";
}

void cfg_bt_0_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "0";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_1_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "1";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_2_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "2";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_3_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "3";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_4_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "4";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_5_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "5";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_6_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "6";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_7_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "7";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_8_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "8";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void cfg_bt_9_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		cfg_password += "9";
		Serial.println(cfg_password);
		check_cfg_ok();
	}
}

void config_buttons()
{
	int x_offset = 60;

	cfg_bt_0 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_0, &bt_style, 0);
	lv_obj_align(cfg_bt_0, LV_ALIGN_CENTER, -2 * x_offset, -30);
	lv_obj_t *label_cfg_bt_0 = lv_label_create(cfg_bt_0);
	lv_label_set_text(label_cfg_bt_0, "0");
	lv_obj_center(label_cfg_bt_0);
	lv_obj_add_event_cb(cfg_bt_0, cfg_bt_0_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_1 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_1, &bt_style, 0);
	lv_obj_align(cfg_bt_1, LV_ALIGN_CENTER, -x_offset, -30);
	lv_obj_t *label_cfg_bt_1 = lv_label_create(cfg_bt_1);
	lv_label_set_text(label_cfg_bt_1, "1");
	lv_obj_center(label_cfg_bt_1);
	lv_obj_add_event_cb(cfg_bt_1, cfg_bt_1_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_2 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_2, &bt_style, 0);
	lv_obj_align(cfg_bt_2, LV_ALIGN_CENTER, 0, -30);
	lv_obj_t *label_cfg_bt_2 = lv_label_create(cfg_bt_2);
	lv_label_set_text(label_cfg_bt_2, "2");
	lv_obj_center(label_cfg_bt_2);
	lv_obj_add_event_cb(cfg_bt_2, cfg_bt_2_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_3 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_3, &bt_style, 0);
	lv_obj_align(cfg_bt_3, LV_ALIGN_CENTER, x_offset, -30);
	lv_obj_t *label_cfg_bt_3 = lv_label_create(cfg_bt_3);
	lv_label_set_text(label_cfg_bt_3, "3");
	lv_obj_center(label_cfg_bt_3);
	lv_obj_add_event_cb(cfg_bt_3, cfg_bt_3_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_4 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_4, &bt_style, 0);
	lv_obj_align(cfg_bt_4, LV_ALIGN_CENTER, 2 * x_offset, -30);
	lv_obj_t *label_cfg_bt_4 = lv_label_create(cfg_bt_4);
	lv_label_set_text(label_cfg_bt_4, "4");
	lv_obj_center(label_cfg_bt_4);
	lv_obj_add_event_cb(cfg_bt_4, cfg_bt_4_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_5 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_5, &bt_style, 0);
	lv_obj_align(cfg_bt_5, LV_ALIGN_CENTER, -2 * x_offset, 20);
	lv_obj_t *label_cfg_bt_5 = lv_label_create(cfg_bt_5);
	lv_label_set_text(label_cfg_bt_5, "5");
	lv_obj_center(label_cfg_bt_5);
	lv_obj_add_event_cb(cfg_bt_5, cfg_bt_5_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_6 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_6, &bt_style, 0);
	lv_obj_align(cfg_bt_6, LV_ALIGN_CENTER, -x_offset, 20);
	lv_obj_t *label_cfg_bt_6 = lv_label_create(cfg_bt_6);
	lv_label_set_text(label_cfg_bt_6, "6");
	lv_obj_center(label_cfg_bt_6);
	lv_obj_add_event_cb(cfg_bt_6, cfg_bt_6_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_7 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_7, &bt_style, 0);
	lv_obj_align(cfg_bt_7, LV_ALIGN_CENTER, 0, 20);
	lv_obj_t *label_cfg_bt_7 = lv_label_create(cfg_bt_7);
	lv_label_set_text(label_cfg_bt_7, "7");
	lv_obj_center(label_cfg_bt_7);
	lv_obj_add_event_cb(cfg_bt_7, cfg_bt_7_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_8 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_8, &bt_style, 0);
	lv_obj_align(cfg_bt_8, LV_ALIGN_CENTER, x_offset, 20);
	lv_obj_t *label_cfg_bt_8 = lv_label_create(cfg_bt_8);
	lv_label_set_text(label_cfg_bt_8, "8");
	lv_obj_center(label_cfg_bt_8);
	lv_obj_add_event_cb(cfg_bt_8, cfg_bt_8_click, LV_EVENT_CLICKED, NULL);

	cfg_bt_9 = lv_btn_create(screen_config);
	lv_obj_add_style(cfg_bt_9, &bt_style, 0);
	lv_obj_align(cfg_bt_9, LV_ALIGN_CENTER, 2 * x_offset, 20);
	lv_obj_t *label_cfg_bt_9 = lv_label_create(cfg_bt_9);
	lv_label_set_text(label_cfg_bt_9, "9");
	lv_obj_center(label_cfg_bt_9);
	lv_obj_add_event_cb(cfg_bt_9, cfg_bt_9_click, LV_EVENT_CLICKED, NULL);
}
