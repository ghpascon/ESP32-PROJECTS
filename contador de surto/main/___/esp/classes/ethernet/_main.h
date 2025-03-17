#include "libs.h"
#include "vars.h"
#include "eth_pins.h"
#include "eth_callback.h"

class ETHERNET_ESP
{
public:
    void setup()
    {
        WiFi.onEvent(WiFiEvent);

        if (!ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE))
        {
            Serial.println("ETH start Failed!");
            ESP.restart();
        }

        if (dhcp)
            return;

        if (!ETH.config(staticIP, gateway, subnet, dns, dns) == false)
        {
            Serial.println("Configuration failed.");
            ESP.restart();
        }
    }
};