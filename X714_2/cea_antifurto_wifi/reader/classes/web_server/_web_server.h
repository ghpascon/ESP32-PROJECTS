#include "vars.h"

#include "post_cmd.h"

#include "script_all.h"
#include "script_ant_config.h"
#include "script_reader_config.h"
#include "script_reader.h"
#include "script_reader_modes.h"
#include "script_gpo_test.h"
#include "script_last_packs.h"

class WEB_SERVER
{
public:
    void setup()
    {
        if (config_mode)
        {
            config_web_server();
            style_web_server();
            routes_web_server();
            script_web_server();
            server.begin();
            if (debug_mode)
                Serial.println(WiFi.softAPIP());
        }

        else
        {
            wifi_config();
        }
    }

    void config_web_server()
    {
        String mac = WiFi.macAddress();
        const String ap_ssid = "X714-" + String(mac);
        const char *ap_password = "smartx12345";
        WiFi.softAP(ap_ssid.c_str(), ap_password);
    }

    void style_web_server()
    {
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/style.css", "text/css"); });

        server.on("/FONT_SMARTX.woff", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/FONT_SMARTX.woff", "font/woff"); });
    }

    void routes_web_server()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/home.html", "text/html"); });

        server.on("/reader", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/reader.html", "text/html"); });

        server.on("/ant_config", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/ant_config.html", "text/html"); });

        server.on("/reader_config", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/reader_config.html", "text/html"); });

        server.on("/reader_modes", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/reader_modes.html", "text/html"); });

        server.on("/gpo_test", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/gpo_test.html", "text/html"); });

        server.on("/last_packs", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/last_packs.html", "text/html"); });
    }
    void script_web_server()
    {
        all_script();
        reader_script();
        config_ant_script();
        config_reader_script();
        reader_modes_script();
        gpo_test_script();
        last_packs_script();
    }

    void wifi_config()
    {
        WiFi.begin(ssid, password_wifi);
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

    void post()
    {
        // nao é necessario definir o tempo
        const int post_time = 10000;
        static unsigned long current_post_time = -post_time;

        if (millis() - current_post_time < post_time)
            return;

        if (!connected)
            return;

        if (posted)
            return;

        current_post_time = millis();
        make_post(get_last_tags());
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
        const int post_timeout_time = 10000;
        static unsigned long current_post_timeout_time = 0;

        if (!posted)
            current_post_timeout_time = millis();

        if (millis() - current_post_timeout_time > post_timeout_time)
            ESP.restart();
    }

    String get_last_tags()
    {
        String last_tags;
        for (int i = 0; i < max_tags; i++)
        {
            if (tags[i].epc == "")
                break;

            last_tags += String(tags[i].epc) + ",";
        }
        last_tags += ",";
        last_tags.replace(",,", "");

        tag_commands.clear_tags();

        return last_tags;
    }
};