void all_script()
{
    server.on("/read_on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                if(!gpi_start)
                    read_on = !read_on;
                request->send(200, "application/json", String(read_on)); });

    server.on("/clear_tags", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        tag_commands.clear_tags();
    request->send(200, "application/json", "TAGS CLEARED"); });

    server.on("/reset", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                ESP.restart();
    request->send(200, "application/json", "RESET"); });
}
