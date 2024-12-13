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

  start_task_1();

  if (client == 1) {
    mode = 0;
    door_mode = 0;
  }
}

void start_task_1() {
  xTaskCreatePinnedToCore(
    async_task_1,  // Função da tarefa
    "async_1",     // Nome da tarefa
    4096,          // Tamanho da pilha
    NULL,          // Parâmetros para a tarefa
    1,             // Prioridade da tarefa
    NULL,          // Handle da tarefa
    1              // Núcleo (Core 1)
  );
}

static void async_task_1(void *pvParameters) {
  while (true) {
    serial_port.check();

    if (client == 1) {
      box_num = "1";
      box_qtd = 1;
    }
    lcm_display.check();
    lcm_display.set_msg();
    lcm_display.send_data();
    lcm_display.check_metrics();
    lcm_display.load_screen_on_start();

    led_rgb.state();

    config_file_commands.save_config();
  }
}

void loop() {
  esp_task_wdt_reset();
  pins.check_inputs();
  motor_state.functions();
  pins.set_outputs();
}
