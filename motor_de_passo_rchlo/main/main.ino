#include "libs.h"
#include "vars.h"

void setup() {
  Serial.begin(115200);
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);
  pins.setup();
}

void loop() {
  esp_task_wdt_reset();

  pins.check_inputs();
  pins.set_outputs();

  reset.check();
}
