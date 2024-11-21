#include "vars.h"

class SERIAL_PORT
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial2.begin(115200, SERIAL_8N1, rx1_pin, tx1_pin);
    }
    
    void check()
    {
        if (!Serial.available())
            return;
        String cmd = Serial.readStringUntil('\n');
        cmd.replace(" ", "");
        cmd.replace("\r", "");
        cmd.replace("\n", "");
        cmd.toLowerCase();
        Serial.println(cmd);
    }
};
