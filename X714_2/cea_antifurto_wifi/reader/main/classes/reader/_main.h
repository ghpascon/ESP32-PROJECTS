#include "vars.h"
#include "reader__commands.h"
#include "reader_periodic.h"
#include "reader_read_commands.h"
#include "reader_serial.h"
#include "reader_setup.h"
#include "reader_verifications.h"
#include "reader_write_commands.h"

class READER : public serial_reader, public reader_read_on_commands, public reader_write_commands, public setup_commands_reader, public periodic_commands_reader, public reader_verifications
{
public:
	void functions()
	{
		check_serial();
		reader_verify();

		if (!answer_rec)
			return;

		if (!setup_done)
		{
			setup();
			return;
		}

		periodic_reader_loop();

		if (read_on && answer_rec)
			read_on_functions();
	}

	void setup_reader()
	{
		config_file_commands.save_config();
		setup_done = false;
		step = 0;
	}

	void setup()
	{
		if (step == 0)
			start_reader();
		else if (step == 1)
			set_reader_adress(0x00);
		else if (step == 2)
			reader_band();
		else if (step == 3)
			reader_work_mode();
		else if (step == 4)
			reader_session();
		else if (step == 5)
			set_active_ant();
		else if (step == 6)
			set_ant_power();
		else if (step == 7)
			set_ant_check();
		else if (step == 8)
			set_reader_time();
		else if (step == 9)
			set_ant_pulse();
		else if (step == 10)
			set_retry_write(0x03);
		else if (step == 11)
			query_parameters();
		else if (step == 12)
			set_write_power(write_power);
		else
		{
			Serial.println("#SETUP_DONE");
			X714_USB.println("#SETUP_DONE");
			setup_done = true;
		}
	}

	void periodic_reader_loop()
	{
		const int periodic_time = 30000;
		static unsigned long current_periodic_time = -periodic_time;
		if (millis() - current_periodic_time < periodic_time)
			return;
		current_periodic_time = millis();
		get_temp();
	}

	void read_on_functions()
	{
		read_on_command();
	}
};