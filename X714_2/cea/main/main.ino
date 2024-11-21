#include "libs.h"
#include "vars.h"

void setup() {
  serial_port.setup();

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);

  config_file_commands.get_config();

  web_server.setup();

  tag_commands.clear_tags();
  last_packs.clear();
  
  rgb.setup();

  pins.setup();
}

void loop() {
  esp_task_wdt_reset();

  pins.check_inputs();

  reader_module.functions();
  serial_port.functions();
  rgb.state();

  pins.set_outputs();
}
