lv_obj_t *bt_0;
lv_obj_t *bt_1;
lv_obj_t *bt_2;
lv_obj_t *bt_3;
lv_obj_t *bt_4;
lv_obj_t *bt_5;
lv_obj_t *bt_6;
lv_obj_t *bt_7;
lv_obj_t *bt_8;
lv_obj_t *bt_9;

void check_insp_ok()
{
	if (device_state == 0)
	{
		password = "";
		wrong_password = false;
		return;
	}
	if (password.length() < secret.length())
		return;

	password = password.substring(0, secret.length());

	if (password == secret)
	{
		password_ok = true;
		device_state = 0;
		wrong_password = false;
	}
	else
		wrong_password = true;

	password = "";
}

void bt_0_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "0";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_1_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "1";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_2_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "2";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_3_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "3";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_4_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "4";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_5_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "5";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_6_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "6";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_7_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "7";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_8_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "8";
		Serial.println(password);
		check_insp_ok();
	}
}

void bt_9_click(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		password += "9";
		Serial.println(password);
		check_insp_ok();
	}
}

void inspec_buttons()
{
	int x_offset = 60;

	bt_0 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_0, &bt_style, 0);
	lv_obj_align(bt_0, LV_ALIGN_CENTER, -2 * x_offset, -30);
	lv_obj_t *label_bt_0 = lv_label_create(bt_0);
	lv_label_set_text(label_bt_0, "0");
	lv_obj_center(label_bt_0);
	lv_obj_add_event_cb(bt_0, bt_0_click, LV_EVENT_CLICKED, NULL);

	bt_1 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_1, &bt_style, 0);
	lv_obj_align(bt_1, LV_ALIGN_CENTER, -x_offset, -30);
	lv_obj_t *label_bt_1 = lv_label_create(bt_1);
	lv_label_set_text(label_bt_1, "1");
	lv_obj_center(label_bt_1);
	lv_obj_add_event_cb(bt_1, bt_1_click, LV_EVENT_CLICKED, NULL);

	bt_2 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_2, &bt_style, 0);
	lv_obj_align(bt_2, LV_ALIGN_CENTER, 0, -30);
	lv_obj_t *label_bt_2 = lv_label_create(bt_2);
	lv_label_set_text(label_bt_2, "2");
	lv_obj_center(label_bt_2);
	lv_obj_add_event_cb(bt_2, bt_2_click, LV_EVENT_CLICKED, NULL);

	bt_3 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_3, &bt_style, 0);
	lv_obj_align(bt_3, LV_ALIGN_CENTER, x_offset, -30);
	lv_obj_t *label_bt_3 = lv_label_create(bt_3);
	lv_label_set_text(label_bt_3, "3");
	lv_obj_center(label_bt_3);
	lv_obj_add_event_cb(bt_3, bt_3_click, LV_EVENT_CLICKED, NULL);

	bt_4 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_4, &bt_style, 0);
	lv_obj_align(bt_4, LV_ALIGN_CENTER, 2 * x_offset, -30);
	lv_obj_t *label_bt_4 = lv_label_create(bt_4);
	lv_label_set_text(label_bt_4, "4");
	lv_obj_center(label_bt_4);
	lv_obj_add_event_cb(bt_4, bt_4_click, LV_EVENT_CLICKED, NULL);

	bt_5 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_5, &bt_style, 0);
	lv_obj_align(bt_5, LV_ALIGN_CENTER, -2 * x_offset, 20);
	lv_obj_t *label_bt_5 = lv_label_create(bt_5);
	lv_label_set_text(label_bt_5, "5");
	lv_obj_center(label_bt_5);
	lv_obj_add_event_cb(bt_5, bt_5_click, LV_EVENT_CLICKED, NULL);

	bt_6 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_6, &bt_style, 0);
	lv_obj_align(bt_6, LV_ALIGN_CENTER, -x_offset, 20);
	lv_obj_t *label_bt_6 = lv_label_create(bt_6);
	lv_label_set_text(label_bt_6, "6");
	lv_obj_center(label_bt_6);
	lv_obj_add_event_cb(bt_6, bt_6_click, LV_EVENT_CLICKED, NULL);

	bt_7 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_7, &bt_style, 0);
	lv_obj_align(bt_7, LV_ALIGN_CENTER, 0, 20);
	lv_obj_t *label_bt_7 = lv_label_create(bt_7);
	lv_label_set_text(label_bt_7, "7");
	lv_obj_center(label_bt_7);
	lv_obj_add_event_cb(bt_7, bt_7_click, LV_EVENT_CLICKED, NULL);

	bt_8 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_8, &bt_style, 0);
	lv_obj_align(bt_8, LV_ALIGN_CENTER, x_offset, 20);
	lv_obj_t *label_bt_8 = lv_label_create(bt_8);
	lv_label_set_text(label_bt_8, "8");
	lv_obj_center(label_bt_8);
	lv_obj_add_event_cb(bt_8, bt_8_click, LV_EVENT_CLICKED, NULL);

	bt_9 = lv_btn_create(screen_inspec);
	lv_obj_add_style(bt_9, &bt_style, 0);
	lv_obj_align(bt_9, LV_ALIGN_CENTER, 2 * x_offset, 20);
	lv_obj_t *label_bt_9 = lv_label_create(bt_9);
	lv_label_set_text(label_bt_9, "9");
	lv_obj_center(label_bt_9);
	lv_obj_add_event_cb(bt_9, bt_9_click, LV_EVENT_CLICKED, NULL);
}
