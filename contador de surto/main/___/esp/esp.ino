#include "libs.h"
#include "vars.h"

void setup() {
  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  serial_port.setup();
  
  config_file_commands.get_config();
  ethernet_esp.setup();
  pins.setup();

  serial_port.get_data();

  lightning_sensor.setup();
}

void loop() {
  esp_task_wdt_reset();
  serial_port.functions();
  pins.check_inputs();
  esp_post.is_connected();
  output_surge.check();
  pins.set_outputs();
  lightning_sensor.check();
}
