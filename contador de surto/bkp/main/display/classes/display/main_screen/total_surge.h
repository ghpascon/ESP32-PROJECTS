lv_obj_t *label_total_surge;

void total_surge_label()
{
	label_total_surge = lv_label_create(device_state_obj);
	lv_label_set_text(label_total_surge, "---");
	lv_obj_add_style(label_total_surge, &label_style, 0);
	lv_obj_align(label_total_surge, LV_ALIGN_CENTER, 0, 15);
}

void att_total_surge_status()
{
	lv_label_set_text(label_total_surge, String("Qtd. de Surtos: " + total_surge).c_str());
}