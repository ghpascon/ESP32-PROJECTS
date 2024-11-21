class web_server_endpoints
{
public:
    void endpoints()
    {
        server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total)
                  {
                String receivedString;
                String current_tag;
                String SEP=",";
                for (size_t i = 0; i < len; i++)
                {
                    receivedString += (char)data[i];
                }

                while(true){
                    int sep_index = receivedString.indexOf(SEP);
                    if (sep_index==-1)
                    {
                        add_command(receivedString);
                        break;
                    }
                    current_tag = receivedString.substring(0,sep_index);
                    add_command(current_tag);
                    receivedString = receivedString.substring(sep_index + 1);
                }                      
                  request->send(200, "text/plain", "String recebida: " + receivedString); });

        server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
                  { 
                    String json = get_json_commands();
                    clear_commands();
                    request->send(200, "application/json", json); });
    }
};