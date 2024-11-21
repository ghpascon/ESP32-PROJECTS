#include "libs.h"
#include "vars.h"

void setup() {
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL); 
  
  serial_port.setup();
  
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
  }

  config_file_commands.get_config();

  web_server.setup();

  pins.setup();

  led_rgb.setup();

  serial_port.send_sts();
}

void loop() {
  esp_task_wdt_reset();

  serial_port.functions();
  pins.check_inputs();

  motor_state.functions();

  pins.set_outputs();
  led_rgb.state();
}
