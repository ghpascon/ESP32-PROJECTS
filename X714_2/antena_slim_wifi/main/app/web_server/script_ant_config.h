void config_ant_script()
{
    server.on("/save_parameters", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        antena[0].active = 0;
        antena[1].active = 0;
        antena[2].active = 0;
        antena[3].active = 0;

        if (request->hasParam("ANT_1_POWER", true))
        {
            antena[0].power = (request->getParam("ANT_1_POWER", true)->value()).toInt();
        }
        if (request->hasParam("ANT_2_POWER", true))
        {
            antena[1].power = (request->getParam("ANT_2_POWER", true)->value()).toInt();
        }
        if (request->hasParam("ANT_3_POWER", true))
        {
            antena[2].power = (request->getParam("ANT_3_POWER", true)->value()).toInt();
        }
        if (request->hasParam("ANT_4_POWER", true))
        {
            antena[3].power = (request->getParam("ANT_4_POWER", true)->value()).toInt();
        }

        if (request->hasParam("ANT_1_RSSI", true))
        {
            antena[0].rssi = (request->getParam("ANT_1_RSSI", true)->value()).toInt();
        }
        if (request->hasParam("ANT_2_RSSI", true))
        {
            antena[1].rssi = (request->getParam("ANT_2_RSSI", true)->value()).toInt();
        }
        if (request->hasParam("ANT_3_RSSI", true))
        {
            antena[2].rssi = (request->getParam("ANT_3_RSSI", true)->value()).toInt();
        }
        if (request->hasParam("ANT_4_RSSI", true))
        {
            antena[3].rssi = (request->getParam("ANT_4_RSSI", true)->value()).toInt();
        }

        if (request->hasParam("ANT_1_CHECK", true))
        {
            antena[0].active = 1;
        }
        if (request->hasParam("ANT_2_CHECK", true))
        {
            antena[1].active = 1;
        }
        if (request->hasParam("ANT_3_CHECK", true))
        {
            antena[2].active = 1;
        }
        if (request->hasParam("ANT_4_CHECK", true))
        {
            antena[3].active = 1;
        }

        for (int i = 0; i < ant_qtd; i++)
        {
            antena[i].rssi = max(antena[i].rssi, min_rssi);
            antena[i].power = constrain(antena[i].power, min_power, max_power);
        }

        reader_module.setup_reader();

        request->send(200, "text/plain", "Dados recebidos com sucesso"); });

    server.on("/get_config", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // Example configuration data
        String json = "{";
        for (int i = 0; i < ant_qtd; i++)
        {
            json += "\"ANT_" + String(i + 1) + "_CHECK\":" + String(antena[i].active) + ",";
            json += "\"ANT_" + String(i + 1) + "_POWER\":\"" + String(antena[i].power) + "\",";
            json += "\"ANT_" + String(i + 1) + "_RSSI\":\"" + String(antena[i].rssi) + "\",";
        }
        json += "}";

        json.replace(",}", "}");

        request->send(200, "application/json", json); });

    server.on("/table_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 4;
        int col = 4;
        String data[row][col] = {
            {"A1", String(antena[0].active ? "ON" : "OFF"), String(antena[0].power), String(antena[0].rssi)},
            {"A2", String(antena[1].active ? "ON" : "OFF"), String(antena[1].power), String(antena[1].rssi)},
            {"A3", String(antena[2].active ? "ON" : "OFF"), String(antena[2].power), String(antena[2].rssi)},
            {"A4", String(antena[3].active ? "ON" : "OFF"), String(antena[3].power), String(antena[3].rssi)}};

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
