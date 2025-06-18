#include "vars.h"
#include "screens.h"
#include "check.h"
#include "string_display.h"

class LCM_DISPLAY : public check_display, public string_display
{
public:
    void setup()
    {
        Lcm.begin();
        Lcm.changeBacklight(100);
    }

    void send_data()
    {
        const int send_time = 5000;
        static unsigned long current_send_time = 0;
        if (millis() - current_send_time < send_time)
            return;
        current_send_time = millis();

        retry_display.write(retry);
        speed_display.write(speed);

        String instruction_label_msg = instruction_messages[step];
        if (step == 6 || step == 7)
            instruction_label_msg += "\n" + state_msg;
        display_instruction_label.write(instruction_label_msg);

        draw_metrics();

    }

    void load_screen_on_start()
    {
        const int load_time = 5000;
        static bool loaded = false;
        if (loaded)
            return;

        Lcm.changePicId(load_screen);

        if (millis() > load_time)
        {
            Lcm.changePicId(op_screen);
            loaded = true;
        }
    }
};
