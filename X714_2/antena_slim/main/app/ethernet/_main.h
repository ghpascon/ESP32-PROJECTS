#include "libs.h"
#include "vars.h"
#include "eth_pins.h"
#include "eth_callback.h"
#include "eth_post.h"

class ETHERNET_ESP
{
public:
    void setup()
    {
        WiFi.onEvent(WiFiEvent);

#ifdef ETH_POWER_PIN
        pinMode(ETH_POWER_PIN, OUTPUT);
        digitalWrite(ETH_POWER_PIN, HIGH);
#endif

#if CONFIG_IDF_TARGET_ESP32
        if (!ETH.begin(ETH_TYPE, ETH_ADDR, ETH_MDC_PIN,
                       ETH_MDIO_PIN, ETH_RESET_PIN, ETH_CLK_MODE))
        {
            Serial.println("ETH start Failed!");
        }
#else
        if (!ETH.begin(ETH_PHY_W5500, 1, ETH_CS_PIN, ETH_INT_PIN, ETH_RST_PIN,
                       SPI3_HOST,
                       ETH_SCLK_PIN, ETH_MISO_PIN, ETH_MOSI_PIN))
        {
            Serial.println("ETH start Failed!");
        }
#endif
        payload.reserve(55000);
    }

    void post_tags()
    {
        const int time = 10000;
        static unsigned long current_time = millis();

        if (millis() - current_time < time || !eth_connected || posted)
            return;

        current_time = millis();
        Serial.println("Start posting...");

        if (current_tag == 0)
        {
            payload = "{";
            payload += "\"device\":\"" + esp_name + "\",";
            payload += "\"event_type\":\"keep_alive\",";
            payload += "\"event_data\":{}";
            payload += "}";
            make_post(payload);
            Serial.println("End posting");
            return;
        }

        payload = "[";

        bool has_tags = false;

        for (int i = 0; i < max_tags; i++)
        {
            if (tags[i].epc == "")
                continue;

            has_tags = true;

            payload += "{";
            payload += "\"device\":\"" + esp_name + "\",";
            payload += "\"event_type\":\"tag\",";
            payload += "\"event_data\":{";
            payload += "\"device\":\"" + esp_name + "\",";
            payload += "\"epc\":\"" + tags[i].epc + "\",";
            payload += "\"tid\":\"" + tags[i].tid + "\",";
            payload += "\"ant\":" + String(tags[i].ant_number) + ",";
            payload += "\"rssi\":" + String(tags[i].rssi);
            payload += "}},";
        }

        if (has_tags)
        {
            if (payload.endsWith(","))
            {
                payload.remove(payload.length() - 1);
            }
            payload += "]";
        }
        else
        {
            payload = "[]";
        }

        make_post(payload);
        tag_commands.clear_tags();
        Serial.println("End posting");
    }
};
