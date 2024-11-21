bool send_post = false;
const int post_delay = 10000;
static unsigned long current_post_delay = -post_delay;

void check_post() {
  if (!connected) {
    static int last_lightning = 0;
    if (last_lightning != lightning_to_send) salvar_config();
    last_lightning = lightning_to_send;
    return;
  }
  if (send_post || (lightning_to_send == 0 && total_lightning != "---") || millis() - current_post_delay < post_delay) return;
  send_post = true;

  xTaskCreatePinnedToCore(
    post_to_api,  // Função da tarefa
    "Task1",      // Nome da tarefa
    4096,         // Tamanho da pilha
    NULL,         // Parâmetros para a tarefa
    1,            // Prioridade da tarefa
    NULL,         // Handle da tarefa
    1             // Núcleo (Core 1)
  );
}

void post_to_api(void* pvParameters) {
  const int current_lightning_to_send = lightning_to_send;
  String to_post = "{\"sensorType\":\"lightning\",\"value\":\"{value}\",\"name\":\"{name}\",\"manut\":\"{manut_status_ok}\"}";
  to_post.replace("{value}", String(current_lightning_to_send));
  to_post.replace("{name}", String(nome));
  to_post.replace("{manut_status_ok}", String(manut_status_ok ? "ok" : "nok"));
  Serial.println(to_post);
  HTTPClient http;

  http.begin(api);
  Serial.println("ENVIANDO POST");

  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(to_post);

  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("Resposta do servidor: " + response);
    lightning_to_send -= current_lightning_to_send;
    display_post_response = "SUCESSO: ";
    display_post_response += String(httpResponseCode);
    total_lightning = response.substring(response.indexOf(":") + 1);
    total_lightning.replace(" ", "");
  } else {
    Serial.println("Erro ao enviar POST request: " + String(httpResponseCode));
    display_post_response = "11";
    current_post_delay = millis();
  }


  http.end();

  salvar_config();

  send_post = false;

  Serial.println("POST ENVIADO");

  vTaskDelete(NULL);
}