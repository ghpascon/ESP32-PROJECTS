void config_page_script()
{
    server.on("/enviar_parametros_config_page", HTTP_POST, [](AsyncWebServerRequest *request)
              {
    if (request->hasParam("IP", true)) {
        IP = request->getParam("IP", true)->value();
    }
    if (request->hasParam("GATEWAY", true))
    {
        GATEWAY = request->getParam("GATEWAY", true)->value();
    }
    if (request->hasParam("SUBNET", true))
    {
        SUBNET = request->getParam("SUBNET", true)->value();
    }
    if (request->hasParam("DNS", true))
    {
        DNS = request->getParam("DNS", true)->value();
    }
    if (request->hasParam("URL", true))
    {
        url = request->getParam("URL", true)->value();
    }

    config_file_commands.get_ip(IP, 0);
    config_file_commands.get_ip(GATEWAY, 1);
    config_file_commands.get_ip(SUBNET, 2);
    config_file_commands.get_ip(DNS, 3);
    config_file_commands.show_config();

    config_file_commands.save_config();

    request->send(200, "text/plain", "Dados recebidos com sucesso"); });

    server.on("/reset_esp_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    ESP.restart();
    request->send(200, "application/json", "reset"); });

    server.on("/label_att_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    const int row = 5;
    const int col = 2;
    const String json_kv[row][col] = {
        {"IP", String(ip_config[0][0]) + "." + String(ip_config[1][0]) + "." + String(ip_config[2][0]) + "." + String(ip_config[3][0])},
        {"GATEWAY", String(ip_config[0][1]) + "." + String(ip_config[1][1]) + "." + String(ip_config[2][1]) + "." + String(ip_config[3][1])},
        {"SUBNET", String(ip_config[0][2]) + "." + String(ip_config[1][2]) + "." + String(ip_config[2][2]) + "." + String(ip_config[3][2])},
        {"DNS", String(ip_config[0][3]) + "." + String(ip_config[1][3]) + "." + String(ip_config[2][3]) + "." + String(ip_config[3][3])},
        {"URL", url}};

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

    server.on("/table_att_config_page", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    const int row = 5;
    const int col = 2;
    const String data[row][col] = {
        {"IP", String(ip_config[0][0]) + "." + String(ip_config[1][0]) + "." + String(ip_config[2][0]) + "." + String(ip_config[3][0])},
        {"GATEWAY", String(ip_config[0][1]) + "." + String(ip_config[1][1]) + "." + String(ip_config[2][1]) + "." + String(ip_config[3][1])},
        {"SUBNET", String(ip_config[0][2]) + "." + String(ip_config[1][2]) + "." + String(ip_config[2][2]) + "." + String(ip_config[3][2])},
        {"DNS", String(ip_config[0][3]) + "." + String(ip_config[1][3]) + "." + String(ip_config[2][3]) + "." + String(ip_config[3][3])},
        {"URL", url}};

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
