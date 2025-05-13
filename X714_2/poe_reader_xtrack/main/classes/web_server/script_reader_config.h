void config_reader_script()
{
    server.on("/save_reader_parameters", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("select_session", true)) {
            session = (request->getParam("select_session", true)->value()).toInt();
            if (session > max_session)
                session = 0x00;
        }

        if (request->hasParam("gpi_stop_delay", true))
        {
            gpi_stop_delay = (request->getParam("gpi_stop_delay", true)->value()).toInt();
        }

        if (request->hasParam("buzzer_vol", true))
        {
            buzzer_vol = (request->getParam("buzzer_vol", true)->value()).toInt();
        }

        if (debug_mode)
        {
            Serial.println("DADOS SALVOS COM SUCESSO:");
            Serial.println("SESSION: " + String(session, DEC));
            Serial.println("GPI STOP DELAY: :" + String(gpi_stop_delay));
        }
        reader_module.setup_reader();
        request->send(200, "text/plain", "Dados salvos com sucesso"); });

    server.on("/get_reader_config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
            const int row = 3;
            const int col = 2;
            const String json_kv[row][col] = {
                {"session", String(session, DEC)},
                {"gpi_stop_delay", String(gpi_stop_delay)},
                {"buzzer_vol", String(buzzer_vol)}};

            String json = "{";
            for (int i = 0; i < row; i++) {
            json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
            }
            json += "}";
            json.replace(",}", "}");
        if (debug_mode)
            Serial.println(json);
        request->send(200, "application/json", json); });

    server.on("/table_reader_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 3;
        int col = 2;
        String data[row][col] = {
            {"SESSION:", String(session, DEC)},
            {"GPI STOP DELAY:", String(gpi_stop_delay) + "ms"},
            {"buzzer_vol:", String(buzzer_vol)}};

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
