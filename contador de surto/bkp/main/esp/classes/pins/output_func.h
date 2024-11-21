class output_func
{
public:
	void set_outputs()
	{
		dps ? pinMode(out_dps, OUTPUT) : pinMode(out_dps, INPUT_PULLUP);
	}
};