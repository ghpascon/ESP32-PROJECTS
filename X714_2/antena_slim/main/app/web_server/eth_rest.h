void eth_rest()
{
    server.on("/api/read_on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                read_on = true;
                request->send(200, "application/json", String(read_on)); });

    server.on("/api/read_off", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                read_on = false;
                request->send(200, "application/json", String(read_on)); });

    server.on("/api/clear_tags", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                tag_commands.clear_tags();
                request->send(200, "application/json", "TAGS CLEARED"); });

    server.on("/api/get_tags", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String current_tags;
                for (int i = 0; i < max_tags; i++)
                {
                    if (tags[i].epc == "")
                        break;
                    current_tags += "\"" + tags[i].epc + "\",";
                }

                String json = "[" + current_tags + "]";
                json.replace(",]", "]");
                request->send(200, "application/json", json); });

    server.on("/api/antenas", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      request->send(400, "application/json", "{\"status\":\"Invalid JSON\"}");
      return;
    }

    for (int i = 0; i < ant_qtd; i++) {
      String key = "ant_" + String(i + 1);
      if (doc.containsKey(key)) {
        JsonObject ant_obj = doc[key];

        if (ant_obj.containsKey("active"))
            antena[i].active = ant_obj["active"];
        if (ant_obj.containsKey("power"))
            antena[i].power = constrain((int)ant_obj["power"], min_power, max_power);
        if (ant_obj.containsKey("rssi"))
            antena[i].rssi = max((int)ant_obj["rssi"], int(min_rssi));
      }
    }

    request->send(200, "application/json", "{\"status\":\"success\"}"); });

    server.on("/api/status", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
              {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, data);

    if (error) {
      request->send(400, "application/json", "{\"status\":\"Invalid JSON\"}");
      return;
    }

    if (doc.containsKey("status")) {
      status_value = doc["status"].as<String>();
      Serial.println("#status:" + status_value);
      request->send(200, "application/json", "{\"status\":\"" + status_value + "\"}");
    } else {
      request->send(400, "application/json", "{\"error\":\"Missing 'status' key\"}");
    } });
}

void config_page_script()
{
    server.on("/enviar_parametros_config_page", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    if (request->hasParam("url", true))
    {
        url = request->getParam("url", true)->value();
    }

    if (request->hasParam("name", true))
    {
        esp_name = request->getParam("name", true)->value();
    }

    config_file_commands.save_config();

    request->send(200, "text/plain", "Dados recebidos com sucesso"); });

    server.on("/reset_esp_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    ESP.restart();
    request->send(200, "application/json", "reset"); });

    server.on("/label_att_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    const int row = 2;
    const int col = 2;
    const String json_kv[row][col] = {
        {"url", String(url)},
        {"name", String(esp_name)}
    };

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

    server.on("/table_att_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    const int row = 2;
    const int col = 2;
    const String data[row][col] = {
        {"url", String(url)},
        {"name", String(esp_name)}
    };

    String json = "[";
    for (int i = 0; i < row; i++) {
    if (i > 0) json += ",";
    json += "[";
    for (int j = 0; j < col; j++) {
        if (j > 0) json += ",";
        json += "\"" + data[i][j] + "\"";
    }
    json += "]";
    }
    json += "]";

    request->send(200, "application/json", json); });
}
