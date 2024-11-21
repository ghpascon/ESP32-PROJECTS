void check_device_state()
{
	static int last_device_state = 999;
	if (last_device_state == device_state)
		return;

	if (device_state == 2)
		lv_screen_load(screen_emg);

	if (last_device_state == 2)
		lv_screen_load(screen_main);

	last_device_state = device_state;
}