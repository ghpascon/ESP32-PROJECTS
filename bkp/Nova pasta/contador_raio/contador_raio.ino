#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <Arduino.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
#define WATCHDOG_TIMEOUT 5

#include <TFT_eSPI.h>
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#include <LittleFS.h>

//html
#include "html/home.h"
#include "html/css.h"
AsyncWebServer server(80);

#define start_mode_pin 27
#define send_pin 22

bool config_mode = false;
unsigned long reset_config_time = 300000;

bool connected = false;
String display_post_response = "";

int lightning_to_send = 0;
String total_lightning = "---";

//parametros web
String nome;
String rede;
String senha;
String api;

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
