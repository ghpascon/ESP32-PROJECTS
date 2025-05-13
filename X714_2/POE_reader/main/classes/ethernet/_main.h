#include "libs.h"
#include "vars.h"
#include "eth_pins.h"
#include "eth_callback.h"

class ETHERNET_ESP
{
public:
    void setup()
    {

        IPAddress staticIP(ip_config[0][0], ip_config[1][0], ip_config[2][0], ip_config[3][0]);
        IPAddress gateway(ip_config[0][1], ip_config[1][1], ip_config[2][1], ip_config[3][1]);
        IPAddress subnet(ip_config[0][2], ip_config[1][2], ip_config[2][2], ip_config[3][2]);
        IPAddress dns(ip_config[0][3], ip_config[1][3], ip_config[2][3], ip_config[3][3]);

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

        if (dhcp)
            return;

        if (!ETH.config(staticIP, gateway, subnet, dns, dns) == false)
        {
            Serial.println("Configuration failed.");
        }
    }
};
