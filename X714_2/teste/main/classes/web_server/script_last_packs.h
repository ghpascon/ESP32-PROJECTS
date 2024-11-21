void last_packs_script()
{
  server.on("/table_last_packs_att", HTTP_GET, [](AsyncWebServerRequest *request)
            {
        int row = max_packs;
        int col = 1;
        String data[row][col];

        for (int i = 0; i < max_packs; i++)
        {
          data[i][0] = "PACK: " + String(i + 1) + "\n" + String(last_packs_read[i]);
          data[i][0].replace("|", "<br>");
          data[i][0].replace("\n", "<br><br>");
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
