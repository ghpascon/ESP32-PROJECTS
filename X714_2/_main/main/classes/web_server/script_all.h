void all_script()
{
    server.on("/read_on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if(!gpi_start)
                    read_on = !read_on;
                request->send(200, "application/json", String(read_on)); });

    server.on("/clear_tags", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        tag_commands.clear_tags();
    request->send(200, "application/json", "TAGS CLEARED"); });

    server.on("/update_firmware", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    // Verifica se a atualizacao foi bem-sucedida e se o ESP32 deve reiniciar
    bool shouldReboot = !Update.hasError();
    if (shouldReboot) {
        // Envia uma resposta de sucesso antes de reiniciar
        request->send(200, "text/plain", "Atualizacao de firmware bem-sucedida! Reiniciando...");
        Serial.println("Atualizacao de firmware bem-sucedida! Reiniciando...");
        if (!simple_send)
            X714_USB.println("Atualizacao de firmware bem-sucedida! Reiniciando...");
        ESP.restart();

        // O ESP32 reiniciara automaticamente apos a conclusao do Update.end()
    } else {
        // Envia uma resposta de erro
        request->send(500, "text/plain", "Erro na atualizacao de firmware: " );
        Serial.println("Erro na atualizacao de firmware: " );
        if (!simple_send)
            X714_USB.println("Erro na atualizacao de firmware: " );
    } }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
              {
    // Callback para lidar com o processo de upload do arquivo
    if (!index) {
        // Inicio do upload
        Serial.printf("Iniciando upload de firmware: %s\n", filename.c_str());
        // UPDATE_SIZE_UNKNOWN e mais flexivel para uploads via POST
        if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { 
            Update.printError(Serial);
            request->send(500, "text/plain", "Erro ao iniciar a atualizacao: ");
        }
    }

    // Escreve os dados recebidos na flash
    if (len) {
        if (Update.write(data, len) != len) {
            Update.printError(Serial);
            request->send(500, "text/plain", "Erro ao escrever na flash: " );
        }
    }

    // Fim do upload
    if (final) {
        if (Update.end(true)) { // 'true' para reiniciar apos a atualizacao
            Serial.println("Upload de firmware concluido e verificado. O ESP32 ira reiniciar.");
            if (!simple_send)
                X714_USB.println("Upload de firmware concluido e verificado. O ESP32 ira reiniciar.");
            ESP.restart();
        }
        else
        {
            Update.printError(Serial);
            request->send(500, "text/plain", "Erro ao finalizar a atualizacao: ");
        }
    } });
}
