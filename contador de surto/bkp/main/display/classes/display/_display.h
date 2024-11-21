#include "libs.h"
#include "vars.h"
#include "display_setup.h"

class ESP32_DISPLAY
{
public:
	void setup()
	{
		display_setup();
		lv_screen_load(screen_main);
	}

	void att_screen()
	{
		const int att_screen_time = 500;
		static unsigned long current_att_screen_time = 0;
		if (millis() - current_att_screen_time < att_screen_time)
			return;
		current_att_screen_time = millis();

		main_screen_att();
		inspec_screen_att();
		emg_screen_att();
	}

	void att_display()
	{
		att_screen();
		const int att_display_time = 5;
		static unsigned long current_att_display_time = 0;
		if (millis() - current_att_display_time > att_display_time)
		{
			lv_task_handler();
			lv_tick_inc(att_display_time);
		}
	}
};