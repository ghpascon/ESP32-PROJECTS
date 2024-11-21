#include "config_page.h"
#include "endpoints.h"

class web_server_config : private web_server_endpoints, private web_server_config_page
{
public:
    void server_config()
    {
        config_web_server();
        style_web_server();

        config_page();
        endpoints();
        
        clear_commands();
        server.begin();
    }

private:
    void config_web_server()
    {
        const char *ssid = "SMARTX-WIFI-PROTOCOL";
        const char *password = "smartx12345";
        WiFi.softAP(ssid, password);
    }

    void style_web_server()
    {
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/style.css", "text/css"); });
    }
};
