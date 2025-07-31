void config_reader_script()
{
    server.on("/save_reader_parameters", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("simple_send", true)) {
            simple_send = (request->getParam("simple_send", true)->value()).toInt() == 1;
        }

        if (request->hasParam("select_session", true)) {
            session = (request->getParam("select_session", true)->value()).toInt();
            if (session > max_session)
                session = 0x00;
        }

        if (request->hasParam("gpi_stop_delay", true))
        {
            gpi_stop_delay = (request->getParam("gpi_stop_delay", true)->value()).toInt();
        }

        reader_module.setup_reader();
        request->send(200, "text/plain", "Dados salvos com sucesso"); });

    server.on("/get_reader_config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
            const int row = 3;
            const int col = 2;
            const String json_kv[row][col] = {
                {"simple_send", String(simple_send?1:0)},
                {"session", String(session, DEC)},
                {"gpi_stop_delay", String(gpi_stop_delay)}};

            String json = "{";
            for (int i = 0; i < row; i++) {
            json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
            }
            json += "}";
            json.replace(",}", "}");
        request->send(200, "application/json", json); });

    server.on("/table_reader_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 3;
        int col = 2;
        String data[row][col] = {
            {"simple_send", String(simple_send ? 1 : 0)},
            {"SESSION:", String(session, DEC)},
            {"GPI STOP DELAY:", String(gpi_stop_delay) + "ms"}};

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
