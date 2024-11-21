#include "vars.h"
#include "post_cmd.h"

// class ESP_POST : private post_cmd
class ESP_POST
{
public:
    void setup()
    {
        WiFi.begin(rede.c_str(), senha.c_str());
    }

    void is_connected()
    {
        static bool last_connected = false;
        online = WiFi.status() == WL_CONNECTED;

        check_timeout();

        if (last_connected == online)
            return;
        last_connected = online;

        if (online)
        {
            Serial.println("Conectado ao WiFi");
            Serial.print("Endereço IP do ESP32: ");
            Serial.println(WiFi.localIP());
            api_status = "20";
        }
        else
        {
            Serial.println("WIFI LOST");
            api_status = "21";
        }
    }

    void post(String to_post)
    {
        // // nao é necessario definir o tempo
        // const int post_time = 3000;
        // static unsigned long current_post_time = -post_time;

        // if (millis() - current_post_time < post_time)
        //     return;

        if (!online)
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
        const int wifi_timeout_time = 300000;
        static unsigned long current_wifi_timeout_time = 0;

        if (online)
            current_wifi_timeout_time = millis();

        if (millis() - current_wifi_timeout_time > wifi_timeout_time)
            ESP.restart();
    }

    void check_post_timeout()
    {
        const int post_timeout_time = 10000;
        static unsigned long current_post_timeout_time = 0;

        if (!posted)
            current_post_timeout_time = millis();

        if (millis() - current_post_timeout_time > post_timeout_time)
            posted = true;
    }
};