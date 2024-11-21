#include "vars.h"

class PINS
{
public:
    void setup()
    {
        pinMode(led_verde, OUTPUT);
        pinMode(led_vermelho, OUTPUT);
    }

    void state()
    {
        if (eth_connected)
        {
            digitalWrite(led_verde, HIGH);
            digitalWrite(led_vermelho, LOW);
        }
        else
        {
            digitalWrite(led_verde, LOW);
            digitalWrite(led_vermelho, HIGH);
        }
    }
};