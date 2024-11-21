String post_str;

void post_cmd(String jsonPayload)
{
    Serial.println("POST: " + jsonPayload);
    
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0)
    {
        String response = http.getString();
        Serial.println("Resposta do servidor: " + response);
    }
    else
    {
        Serial.println("Erro ao enviar POST request: " + String(httpResponseCode));
    }

}

void post_to_api(void *pvParameters)
{
    http.begin(url);

    Serial.println(post_str);
    while (true)
    {
        int sep_index = post_str.indexOf("@");
        if (sep_index == -1)
            break;
        post_cmd(post_str.substring(0, sep_index));
        post_str = post_str.substring(sep_index + 1);
    }
    posted = false;
    Serial.println("POST CONCLUIDO");

    http.end();

    vTaskDelete(NULL);
}

void make_post(String to_post)
{
    post_str = to_post;
    xTaskCreatePinnedToCore(
        post_to_api, // Função da tarefa
        "Task1",     // Nome da tarefa
        4096,        // Tamanho da pilha
        NULL,        // Parâmetros para a tarefa
        1,           // Prioridade da tarefa
        NULL,        // Handle da tarefa
        1            // Núcleo (Core 1)
    );
    posted = true;
}