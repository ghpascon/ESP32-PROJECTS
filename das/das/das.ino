#include "libs.h"
#include "vars.h"

void setup() {
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL); 
  
  serial_port.setup();
  lcm_display.setup();
  pins.setup();
  led_rgb.setup();

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  config_file_commands.get_config();

  web_server.setup();
}

void loop() {
  esp_task_wdt_reset();

  serial_port.check();

  lcm_display.check();
  lcm_display.set_msg();
  lcm_display.send_data();
  lcm_display.load_screen_on_start();

  pins.check_inputs();
  motor_state.functions();
  pins.set_outputs();

  led_rgb.state();

  config_file_commands.save_config();
}
