#include "libs.h"
#include "vars.h"

void setup() {
  serial_port.setup();

  if (!LittleFS.begin()) {
    return;
  }
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);

  config_file_commands.get_config();

  ethernet_esp.setup();

  web_server.setup();

  tag_commands.clear_tags();
  last_packs.clear();

  pins.setup();

  Serial.println("#SETUP_DONE");
}

void loop() {
  esp_task_wdt_reset();

  web_server.post();

  pins.check_inputs();

  reader_module.functions();
  serial_port.functions();

  pins.set_outputs();
}
