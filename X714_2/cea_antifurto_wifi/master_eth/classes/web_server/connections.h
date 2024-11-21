class connections
{
public:
    void check_connections()
    {
        const int check_time = 10000;
        static unsigned long current_check_time = -check_time;
        if (millis() - current_check_time < check_time)
            return;
        current_check_time = millis();

        String message = "Dispositivos conectados:\n";
        uint8_t numStations = WiFi.softAPgetStationNum();
        message += "Número de dispositivos conectados: " + String(numStations) + "\n";

        Serial.println(message);
        check_timeout_wifi(numStations);
    }

private:
    void config_web_server()
    {
        const char *ssid = "ESP32-WIFI-PROTOCOL";
        const char *password = "123456789";
        WiFi.softAP(ssid, password);
    }

    void check_timeout_wifi(int devices)
    {
        const int wifi_timeout = 300000;
        static unsigned long current_wifi_timeout = 0;

        if (devices > 0)
            current_wifi_timeout = millis();

        if (millis() - current_wifi_timeout > wifi_timeout)
            ESP.restart();
    }
};