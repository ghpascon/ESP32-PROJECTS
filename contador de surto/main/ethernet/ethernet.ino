#include "libs.h"
#include "vars.h"

void setup() {
  Serial.begin(115200);

  ethernet_esp.setup();
}

void loop() {
  esp_post.is_connected();
}