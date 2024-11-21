#include "vars.h"

class WEB_SERVER
{
public:
    void setup()
    {
        config_web_server();
        web_server_css();
        web_server_routes();
        web_server_func();
        server.begin();
    }

    void config_web_server()
    {
        const char *ssid = "SMART_TUNEL";
        const char *password = "smartx12345";
        WiFi.softAP(ssid, password);
    }

    void web_server_css()
    {
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/style.css", "text/css"); });
    }

    void web_server_routes()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/home.html", "text/html"); });

    }

    void web_server_func()
    {
        server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(200, "text/plain", "CURRENT TIME: " + String(millis() / 1000)); });

        server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    String current_status = "";
    current_status += "MOTOR: " + String(motor ? (motor_reverse ? "REVERSE" : "ON") : "OFF");
    current_status += "<br>";
    current_status += "STATUS: " + String(cx_ok ? "CX: OK" : (cx_erro ? "CX: ERRO" : "---"));
    current_status += "<br>";
    current_status += "READING: " + String(read_on ? "ON" : "OFF");
    current_status += "<br>";
    current_status += "SPEED: " + String(speed);
    current_status += "<br>";
    current_status += "RETRY_CNT: " + String(retry_cnt);
    current_status += "<br>";
    current_status += "<br>";
    current_status += "SENSOR_IN: " + String(sensor_in ? "ON" : "OFF");
    current_status += "<br>";
    current_status += "SENSOR_OUT: " + String(sensor_out ? "ON" : "OFF");
    current_status += "<br>";
    current_status += "EMG: " + String(emg ? "ON" : "OFF");
    current_status += "<br>";

    request->send(200, "text/plain", current_status); });

    server.on("/cx_ok_bt", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    cx_ok = true;
    cx_erro = false;
    request->send(200, "text/plain", "cx: ok simulation"); });

    server.on("/cx_erro_bt", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    cx_ok = false;
    cx_erro = true;
    request->send(200, "text/plain", "cx: erro simulation"); });

    server.on("/infinit_retry", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    (retry_cnt == 999) ? retry_cnt = 0 : retry_cnt = 999;
    request->send(200, "text/plain", "cx: erro simulation"); });
    }
};