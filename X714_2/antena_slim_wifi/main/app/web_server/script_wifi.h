void wifi_script()
{
    server.on("/save_wifi_parameters", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("wifi_ssid", true)) {
            wifi_ssid = (request->getParam("wifi_ssid", true)->value());
        }

        if (request->hasParam("wifi_password", true)) {
            wifi_password = (request->getParam("wifi_password", true)->value());
        }
        
        if (request->hasParam("wifi_url", true)) {
            wifi_url = (request->getParam("wifi_url", true)->value());
        }
        
        if (request->hasParam("wifi_name", true)) {
            wifi_name = (request->getParam("wifi_name", true)->value());
        }        

     
        reader_module.setup_reader();
        request->send(200, "text/plain", "Dados salvos com sucesso"); });

    server.on("/get_wifi_config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
            const int row = 4;
            const int col = 2;
            const String json_kv[row][col] = {
                {"wifi_ssid", String(wifi_ssid)},
                {"wifi_password", String(wifi_password)},
                {"wifi_url", String(wifi_url)},
                {"wifi_name", String(wifi_name)}};

            String json = "{";
            for (int i = 0; i < row; i++) {
            json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
            }
            json += "}";
            json.replace(",}", "}");
        request->send(200, "application/json", json); });

    server.on("/table_wifi_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 4;
        int col = 2;
        String data[row][col] = {
                {"wifi_ssid", String(wifi_ssid)},
                {"wifi_password", String(wifi_password)},
                {"wifi_url", String(wifi_url)},
                {"wifi_name", String(wifi_name)}};

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
