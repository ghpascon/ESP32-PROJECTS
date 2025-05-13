#include "vars.h"
#include "script_all.h"
#include "script_ant_config.h"
#include "script_reader_config.h"
#include "script_reader.h"
#include "script_reader_modes.h"
#include "script_gpo_test.h"
#include "script_last_packs.h"
#include "script_config_page.h"
#include "http_post.h"

class WEB_SERVER : public http_post
{
public:
    void setup()
    {
        config_web_server();
        style_web_server();
        routes_web_server();
        script_web_server();
        server.begin();
        if (debug_mode)
            Serial.println(WiFi.softAPIP());
    }

    void config_web_server()
    {
        String mac = WiFi.macAddress();
        const String ssid = "X714-" + String(mac);
        const char *password = "smartx12345";
        WiFi.softAP(ssid.c_str(), password);
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

        server.on("/ethernet_config", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/ethernet_config.html", "text/html"); });
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
        config_page_script();
    }
};