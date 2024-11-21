#include "vars.h"
#include "serial_display.h"

class SERIAL_PORT : private serial_display
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial1.begin(115200, SERIAL_8N1, rx1_pin, tx1_pin);
    }

    void send_sts()
    {
        send_status();
    }

    void functions()
    {
        check_serial_display();
    }
};
