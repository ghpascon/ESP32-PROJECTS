#include "libs.h"
#include "vars.h"

void setup() {
  serial_port.setup();
  if (!LittleFS.begin()) {
    return;
  }

  esp_task_wdt_config_t wdt_config = {
    .timeout_ms = WATCHDOG_TIMEOUT * 1000,
    .idle_core_mask = (1 << portNUM_PROCESSORS) - 1, // Ambos os núcleos
    .trigger_panic = true
  };

  esp_task_wdt_init(&wdt_config);
  esp_task_wdt_add(NULL);

  config_file_commands.get_config();

  ethernet_esp.setup();

  web_server.setup();

  tag_commands.clear_tags();
  last_packs.clear();

  pins.setup();
}

void loop() {
  esp_task_wdt_reset();

  pins.check_inputs();

  reader_module.functions();
  serial_port.functions();
  ethernet_esp.post_tags();

  pins.set_outputs();
}
