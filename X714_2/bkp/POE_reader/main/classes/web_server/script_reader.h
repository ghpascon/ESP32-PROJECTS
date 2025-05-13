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
        int row =current_tag;
        int col = 5;
        String data[row][col];

        for (int i = 0; i < row;i++)
        {
            data[i][0] = String(i+1);
            data[i][1] = String(((tags[i].epc).substring(0, (tags[i].epc).length() / 2)) + "<br>" + ((tags[i].epc).substring((tags[i].epc).length() / 2)));
            data[i][2] = String(((tags[i].tid).substring(0, (tags[i].tid).length() / 2)) + "<br>" + ((tags[i].tid).substring((tags[i].tid).length() / 2)));
            data[i][3] = String(tags[i].ant_number);
            data[i][4] = String(tags[i].rssi);
        }

            String json = "[";
        for (int i = 0; i < row; i++)
        {
            if (i > 0)
                json += ",";
            json += "[";
            for (int j = 0; j < col; j++)
            {
                if (j > 0)
                    json += ",";
                json += "\"" + data[i][j] + "\"";
            }
            json += "]";
        }
        json += "]";
        request->send(200, "application/json", json); });
}
