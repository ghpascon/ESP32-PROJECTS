#include "vars.h"
#include "check_serial.h"

class SERIAL_PORT : public check_serial
{
public:
    void setup()
    {
        Serial2.begin(115200, SERIAL_8N1, rx2_pin, tx2_pin);
    }

    void get()
    {
        Serial2.println("#GET_STATUS");
    }
};
