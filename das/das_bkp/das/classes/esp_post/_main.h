#include "vars.h"
#include "post_cmd.h"

// class ESP_POST : private post_cmd
class ESP_POST
{
public:
    void setup()
    {
        WiFi.begin(ssid, wifi_password);
    }

    void is_connected()
    {
        static bool last_connected = false;
        connected = WiFi.status() == WL_CONNECTED;

        check_timeout();

        if (last_connected == connected)
            return;
        last_connected = connected;

        if (connected)
        {
            Serial.println("Conectado ao WiFi");
            Serial.print("Endereço IP do ESP32: ");
            Serial.println(WiFi.localIP());
        }
        else
        {
            Serial.println("WIFI LOST");
        }
    }

    void post(String to_post)
    {
        if (!connected)
            return;

        if (posted)
            return;

        make_post(to_post);
    }

private:
    void check_timeout()
    {
        check_wifi_timeout();
        check_post_timeout();
    }

    void check_wifi_timeout()
    {
        const int wifi_timeout_time = 30000;
        static unsigned long current_wifi_timeout_time = 0;

        if (connected)
            current_wifi_timeout_time = millis();

        if (millis() - current_wifi_timeout_time > wifi_timeout_time)
            ESP.restart();
    }

    void check_post_timeout()
    {
        const int post_timeout_time = 30000;
        static unsigned long current_post_timeout_time = 0;

        if (!posted)
            current_post_timeout_time = millis();

        if (millis() - current_post_timeout_time > post_timeout_time)
            ESP.restart();
    }
};