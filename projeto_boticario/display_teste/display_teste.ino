#include "libs.h"
#include "vars.h"

void setup() {
  serial_port.setup();
  esp_display.setup();
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);
  serial_port.get();
}

void loop() {
  esp_task_wdt_reset();
  serial_port.check_serial_cmd();
  esp_display.att_display();
}