#include "libs.h"
#include "vars.h"
#include "eth_pins.h"
#include "eth_callback.h"
#include "post.h"

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
        client.setInsecure();
    }

    void post_tags()
    {
        const int time = 10000;
        static unsigned long current_time = millis();
        if (millis() - current_time < time || !eth_connected || posted)
            return;

        current_time = millis();
        if (current_tag == 0)
            return;


        for (int i = 0; i < max_tags; i++)
        {
            tags_to_post[i][0] = tags[i].epc;
            tags_to_post[i][1] = String(tags[i].ant_number);
        }
        create_post_tag();
        tag_commands.clear_tags();
    }
};
