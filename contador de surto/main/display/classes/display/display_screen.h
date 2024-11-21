#include "display_styles.h"
#include "main_screen/_screen.h"
#include "inspec_screen/_screen.h"
#include "emg_screen/_screen.h"
#include "config_screen/_screen.h"

// declarar as screens dentro de vars
void screens_setup()
{
	screen_main = lv_obj_create(NULL);
	lv_obj_clear_flag(screen_main, LV_OBJ_FLAG_SCROLLABLE);

	screen_inspec = lv_obj_create(NULL);

	screen_emg = lv_obj_create(NULL);

	screen_config = lv_obj_create(NULL);
}

void create_display_screen()
{
	create_display_styles();
	screens_setup();
	main_screen();
	inspec_screen();
	emg_screen();
	cgf_screen();
}

