#include "libs.h"
#include "vars.h"
#include "eth_pins.h"
#include "eth_callback.h"
#include "async_post.h"

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
    }

    void post_tags()
    {
        const int time = 3000;
        static unsigned long current_time = millis();
        if (millis() - current_time < time || !eth_connected || posted)
            return;
        current_time = millis();
        if (current_tag == 0)
            return;

        Serial.println("Post tags in " + url);
        make_post(get_tags_to_post());
    }

private:
    String get_tags_to_post()
    {
        String xml = "<msg>";
        xml += "<command>ReportRead</command>";
        xml += "<data>EVENT=";
        xml += "";
        xml += "|DEVICENAME=" + "teste01" + "|ANTENNANAME=1|TAGID=0000000000000000A0000280|</data>";
        xml += "<cmpl>STATE=APPEARED|DATA1=|DATA2=|DATA3=|DATA4=|DATA5=|</cmpl>";
        xml += "</msg>";

        // String to_post = "<tags>";
        // for (int i = 0; i < max_tags; i++)
        // {
        //     if (tags[i].epc == "")
        //         break;
        //     to_post += "<tag>" + tags[i].epc + "</tag>";
        // }

        // to_post += "</tags>";

        tag_commands.clear_tags();
        Serial.println(xml);
        return xml;
    }

};
