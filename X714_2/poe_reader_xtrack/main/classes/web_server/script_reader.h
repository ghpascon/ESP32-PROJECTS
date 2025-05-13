void reader_script()
{
    server.on("/reader_html_info", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    const int row = 5;
    const int col = 2;
    const String json_kv[row][col] = {
        {"reading", String(read_on ? "ON" : "OFF")},
        {"temperature", String(temperatura)},
        {"total_tags", "TOTAL: " + String(current_tag)},
        {"read_button_txt", String(gpi_start ? "GPI" : (read_on ? "STOP" : "READ"))},
        {"read_button_color", String(gpi_start ? "#cccccc" : (read_on ? "#ff0000" : "#00ff00"))}};

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

    server.on("/tags_table_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
            String json = "[" + tags_table + "]";
            json.replace(",]", "]");
            request->send(200, "application/json", json); });
}
