#include "libs.h"
#include "vars.h"

void setup() {
  serial_port.setup();
  lvlg_display.setup();
}

void loop() {
  esp_task_wdt_reset();
  lvlg_display.att_display();
  serial_port.functions();
}
