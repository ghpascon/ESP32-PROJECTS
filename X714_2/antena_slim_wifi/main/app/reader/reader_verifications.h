class reader_verifications
{
public:
	void reader_verify()
	{
		check_read_off();
		check_timeout();
		check_reader_connection();
		reset_no_read();
	}

	void check_read_off()
	{
		static bool last_read = false;
		if (last_read == read_on)
			return;

		last_read = read_on;

		if (read_on)
		{
			tag_commands.clear_tags();
		}
		else
		{
			last_packs.save();
		}
	}

	void check_timeout()
	{
		const int answer_timeout = 1000;
		static unsigned long current_answer_timeout = 0;
		if (answer_rec)
			current_answer_timeout = millis();
		if (millis() - current_answer_timeout > answer_timeout && setup_done)
		{
			myserial.write("#TIMEOUT");
			answer_rec = true;
			setup_done = false;
			step = 0;
		}
	}

	void check_reader_connection()
	{
		const int timeout_reader_connection = 5000;
		static unsigned long current_timeout_reader_connection = 0;
		if (setup_done)
			current_timeout_reader_connection = millis();
		if (millis() - current_timeout_reader_connection > timeout_reader_connection)
		{
			myserial.write("#RESTART");
			ESP.restart();
		}
	}

	void reset_no_read()
	{
		const int timeout_no_read = 1800000;
		static unsigned long current_timeout_no_read = 0;
		if (read_on)
			current_timeout_no_read = millis();
		if (millis() - current_timeout_no_read > timeout_no_read)
			ESP.restart();
	}
};
