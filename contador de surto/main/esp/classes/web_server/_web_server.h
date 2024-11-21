#include "vars.h"

class WEB_SERVER
{
public:
void reset()
{
    const int timeout = 300000;
    if(millis()>timeout)
        ESP.restart();
}

    void setup()
    {
        config_web_server();
        style_web_server();
        routes_web_server();
        script_web_server();
        server.begin();
    }

    void config_web_server()
    {
        String mac = WiFi.macAddress();
        const String ssid = "SURGE_COUNTER-" + String(mac);
        const char *password = "123456789";
        WiFi.softAP(ssid.c_str(), password);
    }

    void style_web_server()
    {
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/style.css", "text/css"); });
    }

    void routes_web_server()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
                  { request->send(LittleFS, "/html/home.html", "text/html"); });
    }

    void script_web_server()
    {
        server.on("/enviar_parametros", HTTP_POST, [](AsyncWebServerRequest *request)
                  {
    if (request->hasParam("nome", true)) {
      nome = request->getParam("nome", true)->value();
    }
    if (request->hasParam("rede", true)) {
      rede = request->getParam("rede", true)->value();
    }
    if (request->hasParam("senha", true)) {
      senha = request->getParam("senha", true)->value();
    }
    if (request->hasParam("url", true))
    {
        url = request->getParam("url", true)->value();
    }

    Serial.println("Nome: " + nome);
    Serial.println("Rede: " + rede);
    Serial.println("Senha: " + senha);
    Serial.println("Url: " + url);

    config_file_commands.save_config();

    request->send(200, "text/plain", "Dados recebidos com sucesso"); });

    server.on("/label_att", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    const int row = 4;
    const int col = 2;
    const String json_kv[row][col] = {
        {"nome", nome},
        {"rede", rede},
        {"senha", senha},
        {"url", url}};

    String json = "{";
    for (int i = 0; i < row; i++) {
      json += "\"" + json_kv[i][0] + "\":\"" + json_kv[i][1] + "\",";
    }
    json += "}";
    json.replace(",}", "}");

    request->send(200, "application/json", json); });

    server.on("/reset_esp", HTTP_GET, [](AsyncWebServerRequest *request)
                  {
    ESP.restart();
    request->send(200, "application/json", "reset"); });

    server.on("/table_att", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        int row = 4;
        int col = 2;
        String data[row][col] = {
            {"NOME:", String(nome)},
            {"REDE:", String(rede)},
            {"SENHA:", String(senha)},
            {"URL:", String(url)}};

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
};