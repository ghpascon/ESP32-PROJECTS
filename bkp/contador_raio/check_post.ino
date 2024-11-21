bool send_post = false;

void check_post() {
  if (!connected) salvar_config();
  if (!connected) return;
  if (lightning_to_send == 0 && total_lightning != "---") return;
  if (send_post) return;
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
  const String to_post = "{\"sensorType\":\"lightning\",\"value\":\"{value}\"}";
  String current_to_post = to_post;
  current_to_post.replace("{value}", String(current_lightning_to_send));


  HTTPClient http;

  http.begin(api);
  Serial.println("ENVIANDO POST");

  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(current_to_post);

  if (httpResponseCode == 200) {
    String response = http.getString();
    Serial.println("Resposta do servidor: " + response);
    lightning_to_send -= current_lightning_to_send;
    display_post_response = "SUCESSO: ";
    total_lightning = response.substring(response.indexOf(":") + 1);
    total_lightning.replace(" ", "");
  } else {
    Serial.println("Erro ao enviar POST request: " + String(httpResponseCode));
    display_post_response = "ERRO: ";
  }
  display_post_response += String(httpResponseCode);

  http.end();

  send_post = false;
  salvar_config();

  Serial.println("POST ENVIADO");

  vTaskDelete(NULL);
}