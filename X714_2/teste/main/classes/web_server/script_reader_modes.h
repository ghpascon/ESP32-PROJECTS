void reader_modes_script()
{
  server.on("/modes_att", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    const int row = 8;
    const int col = 2;
    const String json_kv[row][col] = {
        {"gpi_start_label", String(start_reading ? "START READING" : (gpi_start ? "ON" : "OFF"))},
        {"gpi_start_color", String(start_reading ? "#cccccc" : (gpi_start ? "#00ff00" : "#ff0000"))},
        {"start_reading_label", String(start_reading ? "ON" : "OFF")},
        {"start_reading_color", String(start_reading ? "#00ff00" : "#ff0000")},
        {"ignore_read_label", String(ignore_read ? "ON" : "OFF")},
        {"ignore_read_color", String(ignore_read ? "#00ff00" : "#ff0000")},
        {"always_send_label", String(always_send ? "ON" : "OFF")},
        {"always_send_color", String(always_send ? "#00ff00" : "#ff0000")},
    };

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

  server.on("/start_reading", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        start_reading = !start_reading;
        if (start_reading)
          gpi_start = false;
        config_file_commands.save_config();
        if (debug_mode)
          X714_USB.println("START_READING:" + String(start_reading ? "ON" : "OFF"));
        request->send(200, "application/json", String(start_reading)); });

  server.on("/gpi_start", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
              if(start_reading)
               {
                 request->send(401, "application/json", String("START READ MODE ACTIVE"));
                 return;
                 }
        gpi_start = !gpi_start;
        config_file_commands.save_config();
        if (debug_mode)
          X714_USB.println("GPI_START:" + String(gpi_start ? "ON" : "OFF"));
        request->send(200, "application/json", String(gpi_start)); });

  server.on("/ignore_read", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        ignore_read = !ignore_read;
        config_file_commands.save_config();
        if (debug_mode)
          X714_USB.println("IGNORE_READ:" + String(ignore_read ? "ON" : "OFF"));
        request->send(200, "application/json", String(ignore_read)); });

  server.on("/always_send", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        always_send = !always_send;
        config_file_commands.save_config();
        if (debug_mode)
          X714_USB.println("ALWAYS_SEND:" + String(always_send ? "ON" : "OFF"));
        request->send(200, "application/json", String(always_send)); });
}
