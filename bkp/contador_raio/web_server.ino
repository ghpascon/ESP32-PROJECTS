void config_web_server() {
  const char* ssid = "ESP32-TESTE";
  const char* password = "123456789";
  WiFi.softAP(ssid, password);
}

void web_server() {
  config_web_server();

  style_web_server();
  routes_web_server();
  script_web_server();
  server.begin();
}

void style_web_server() {
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/css", css);
  });
}

void routes_web_server() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    String html = home_html;
    html.replace("@HOME_SCRIPT@", HOME_SCRIPT);
    request->send(200, "text/html", html);
  });
}

void script_web_server() {
  server.on("/enviar_parametros", HTTP_POST, [](AsyncWebServerRequest* request) {
    if (request->hasParam("nome", true)) {
      nome = request->getParam("nome", true)->value();
    }
    if (request->hasParam("rede", true)) {
      rede = request->getParam("rede", true)->value();
    }
    if (request->hasParam("senha", true)) {
      senha = request->getParam("senha", true)->value();
    }
    if (request->hasParam("api", true)) {
      api = request->getParam("api", true)->value();
    }

    Serial.println("Nome: " + nome);
    Serial.println("Rede: " + rede);
    Serial.println("Senha: " + senha);
    Serial.println("Api: " + api);

    salvar_config();

    request->send(200, "text/plain", "Dados recebidos com sucesso");
  });

  server.on("/label_att", HTTP_GET, [](AsyncWebServerRequest* request) {
    const int row = 4;
    const int col = 2;
    const String json_kv[row][col] = {
      { "nome", nome },
      { "rede", rede },
      { "senha", senha },
      { "api", api }
    };

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json);
  });

  server.on("/reset_esp", HTTP_GET, [](AsyncWebServerRequest* request) {
    ESP.restart();
    request->send(200, "application/json", "reset");
  });
}