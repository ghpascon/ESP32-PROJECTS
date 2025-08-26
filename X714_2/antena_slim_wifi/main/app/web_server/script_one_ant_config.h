void config_one_ant_script()
{
    server.on("/save_parameters_one_ant", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        if (request->hasParam("ANT_1_POWER", true))
        {
            antena[0].power = (request->getParam("ANT_1_POWER", true)->value()).toInt();
        }
       

        if (request->hasParam("ANT_1_RSSI", true))
        {
            antena[0].rssi = (request->getParam("ANT_1_RSSI", true)->value()).toInt();
        }
      
        for (int i = 0; i < 1; i++)
        {
        antena[i].rssi = max(antena[i].rssi, min_rssi);
        antena[i].power = constrain(antena[i].power, min_power, max_power);
        }

        reader_module.setup_reader();

        request->send(200, "text/plain", "Dados recebidos com sucesso"); });

    server.on("/get_config_one_ant", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        // Example configuration data
        String json = "{";
        for (int i = 0; i < 1; i++)
        {
            json += "\"ANT_" + String(i + 1) + "_POWER\":\"" + String(antena[i].power) + "\",";
            json += "\"ANT_" + String(i + 1) + "_RSSI\":\"" + String(antena[i].rssi) + "\",";
        }
        json += "}";

        json.replace(",}", "}");

        request->send(200, "application/json", json); });

    server.on("/table_att_one_ant", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 1;
        int col = 3;
        String data[row][col] = {
            {"A1", String(antena[0].power), String(antena[0].rssi)}};

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
