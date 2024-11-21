#include "libs.h"
#include "vars.h"

void setup() {
  Serial.begin(115200);

  if (!LittleFS.begin()) {
    Serial.println("Falha ao montar o sistema de arquivos");
    ESP.restart();
  }

  readFile();

  pinMode(start_mode_pin, INPUT_PULLUP);
  pinMode(send_pin, INPUT_PULLUP);

  if (!digitalRead(start_mode_pin)) config_mode = true;

  (config_mode) ? web_server() : wifi_config();

  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);

  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  esp_task_wdt_reset();
  att_display();

  if (!config_mode) {
    reconnect_wifi();
    check_signal();
    check_post();
    reset_in_config_mode();
  } else {
    if (millis() > reset_config_time) {
      ESP.restart();
    }
  }
}
