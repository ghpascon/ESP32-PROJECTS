void gpo_test_script()
{
  server.on("/gpo_att", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    const int row = 6;
    const int col = 2;
    const String json_kv[row][col] = {
        {"gpo_1_bt_label", String(gpo[0] ? "ON" : "OFF")},
        {"gpo_1_bt_color", String(gpo[0] ? "#00ff00" : "#ff0000")},
        {"gpo_2_bt_label", String(gpo[1] ? "ON" : "OFF")},
        {"gpo_2_bt_color", String(gpo[1] ? "#00ff00" : "#ff0000")},
        {"gpo_3_bt_label", String(gpo[2] ? "ON" : "OFF")},
        {"gpo_3_bt_color", String(gpo[2] ? "#00ff00" : "#ff0000")}};

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

  server.on("/gpo_1_bt", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        gpo[0]=!gpo[0];
        request->send(200, "application/json", String(gpo[0])); });

  server.on("/gpo_2_bt", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        gpo[1]=!gpo[1];
        request->send(200, "application/json", String(gpo[1])); });

  server.on("/gpo_3_bt", HTTP_GET, [](AsyncWebServerRequest *request)
            { 
        gpo[2]=!gpo[2];
        request->send(200, "application/json", String(gpo[2])); });
}
