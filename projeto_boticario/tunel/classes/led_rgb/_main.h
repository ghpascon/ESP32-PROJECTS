#include "vars.h"

class LED_RGB
{
public:
    void setup()
    {
        pinMode(green_pin, OUTPUT);
        pinMode(blue_pin, OUTPUT);
        pinMode(red_pin, OUTPUT);
    }

    void state()
    {
        if (emg)
        {
            digitalWrite(green_pin, LOW);
            digitalWrite(blue_pin, LOW);
            digitalWrite(red_pin, HIGH);
        }
        else if (cx_erro)
        {
            static bool flag_yellow = false;
            flag_yellow = !flag_yellow;

            if (flag_yellow)
            {
                digitalWrite(green_pin, HIGH);
                digitalWrite(blue_pin, LOW);
                digitalWrite(red_pin, LOW);
            }
            else
            {
                digitalWrite(green_pin, LOW);
                digitalWrite(blue_pin, LOW);
                digitalWrite(red_pin, HIGH);
            }
        }
        else if (cx_ok)
        {
            digitalWrite(green_pin, HIGH);
            digitalWrite(blue_pin, LOW);
            digitalWrite(red_pin, LOW);
        }
        else if (motor)
        {
            digitalWrite(green_pin, LOW);
            digitalWrite(blue_pin, HIGH);
            digitalWrite(red_pin, LOW);
        }
        else
        {
            static int flag_white = 0;

            if (flag_white == 0)
            {
                digitalWrite(green_pin, HIGH);
                digitalWrite(blue_pin, LOW);
                digitalWrite(red_pin, LOW);
                flag_white++;
            }
            else if (flag_white == 1)
            {
                digitalWrite(green_pin, LOW);
                digitalWrite(blue_pin, HIGH);
                digitalWrite(red_pin, LOW);
                flag_white++;
            }
            else
            {
                digitalWrite(green_pin, LOW);
                digitalWrite(blue_pin, LOW);
                digitalWrite(red_pin, HIGH);
                flag_white = 0;
            }
        }
    }
};
