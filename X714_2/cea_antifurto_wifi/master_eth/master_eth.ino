#include "libs.h"
#include "vars.h"

void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  config_file_commands.get_config();

  ethernet_esp.setup();

  web_server_esp.setup();

  pins.setup();

  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);
}

void loop() {
  esp_task_wdt_reset();
  web_server_esp.check_connections();
  web_server_esp.post();
  pins.state();
}