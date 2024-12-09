#include "libs.h"
#include "vars.h"

void setup() {
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  serial_port.setup();
  config_file_commands.get_config();
  pins.setup();

  setup_mode ? esp_web_server.setup() : esp_post.setup();

  serial_port.get_data();

  lightning_sensor.setup();
}

void loop() {
  setup_mode ? setup_mode_on() : setup_mode_off();
}

void setup_mode_on() {
  esp_task_wdt_reset();
  serial_port.functions();
  esp_web_server.reset();
}

void setup_mode_off() {
  esp_task_wdt_reset();
  serial_port.functions();
  pins.check_inputs();
  esp_post.is_connected();
  output_surge.check();
  pins.set_outputs();
  lightning_sensor.check();
}
