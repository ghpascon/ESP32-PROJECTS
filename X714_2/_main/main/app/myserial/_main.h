#include "vars.h"

class MySerial
{
public:
    void setup()
    {
        Serial.begin(115200);
        Serial2.begin(57600, SERIAL_8N1, rx_reader_module, tx_reader_module);

        my_keyboard.begin();
        USB.VID(0x0001);
        USB.PID(0x0001);
        USB.manufacturerName("Smartx");
        USB.productName("X714");
        USB.usbAttributes(0x80);
        USB.begin();
        my_usb.begin(115200);
    }

    void write(const String &data, bool all = false)
    {
        Serial.println(data);

        if (!all && simple_send)
            return;

        if (keyboard)
            my_keyboard.println(data);
        my_usb.println(data);
    }

    String check_serial()
    {
        String cmd = "";

        if (Serial.available())
        {
            cmd = Serial.readStringUntil('\n');
        }
        else if (my_usb.available())
        {
            cmd = my_usb.readStringUntil('\n');
        }

        cmd.toLowerCase();
        cmd.replace(" ", "");
        cmd.replace("\r", "");
        cmd.replace("\n", "");

        return cmd;
    }
};
