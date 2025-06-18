#include "vars.h"

class WEB_SERVER
{
    public:
    void setup()
    {
        config_web_server();
        web_server_css();
        web_server_routes();
        web_server_func();
        update_esp();
        server.begin();
    }

    void config_web_server()
    {
        uint64_t chipid = ESP.getEfuseMac();
        char id_str[13];
        sprintf(id_str, "%012llX", chipid);
        const String ssid = "SMTX-TUNEL-" + String(id_str);
        const char* password = "smartx12345";
        WiFi.softAP(ssid.c_str(), password);
    }

    void web_server_css()
    {
        server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request)
                  { request->send(LittleFS, "/html/style.css", "text/css"); });
    }

    void web_server_routes()
    {
        server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
                  { request->send(LittleFS, "/html/home.html", "text/html"); });
    }

    void web_server_func()
    {
        //
        server.on("/time", HTTP_GET, [](AsyncWebServerRequest * request)
                  { request->send(200, "text/plain", "CURRENT TIME: " + String(millis() / 1000)); });

        //
        server.on("/status", HTTP_GET, [](AsyncWebServerRequest * request)
                  {
            String current_status = "";
            current_status += "MOTOR: " + String(motor ? (motor_reverse ? "REVERSE" : "ON") : "OFF");
            current_status += "<br>";
            current_status += "STATUS: " + String(cx_ok ? "CX: OK" : (cx_erro ? "CX: ERRO" : "---"));
            current_status += "<br>";
            current_status += "READING: " + String(read_on ? "ON" : "OFF");
            current_status += "<br>";
            current_status += "BOX_INSIDE: " + String(box_inside ? "ON" : "OFF");
            current_status += "<br>";
            current_status += "<br>";
            current_status += "PERFIL: " + String(mode - 2);
            current_status += "<br>";
            current_status += "SPEED: " + String(speed);
            current_status += "<br>";
            current_status += "RETRY: " + String(retry);
            current_status += "<br>";
            current_status += "<br>";
            current_status += "SENSOR_IN: " + String(sensor_in ? "ON" : "OFF");
            current_status += "<br>";
            current_status += "SENSOR_OUT: " + String(sensor_out ? "ON" : "OFF");
            current_status += "<br>";
            current_status += "EMG: " + String(emg ? "ON" : "OFF");
            request->send(200, "text/plain", current_status);
        });

        //
        server.on("/cx_ok_bt", HTTP_GET, [](AsyncWebServerRequest * request)
                  {
            cx_ok = true;
            cx_erro = false;
            request->send(200, "text/plain", "cx: ok simulation");
        });

        //
        server.on("/cx_erro_bt", HTTP_GET, [](AsyncWebServerRequest * request)
                  {
            cx_ok = false;
            cx_erro = true;
            request->send(200, "text/plain", "cx: erro simulation");
        });

        //
        server.on("/infinit_retry", HTTP_GET, [](AsyncWebServerRequest * request)
                  {
            (retry == 100) ? retry = 0 : retry = 100;
            request->send(200, "text/plain", "cx: erro simulation");
        });
    }

    void update_esp()
    {
        server.on("/update_firmware", HTTP_POST, [](AsyncWebServerRequest * request)
            {
            // Verifica se a atualizacao foi bem-sucedida e se o ESP32 deve reiniciar
            bool shouldReboot = !Update.hasError();
            if (shouldReboot)
            {
                // Envia uma resposta de sucesso antes de reiniciar
                request->send(200, "text/plain", "Atualizacao de firmware bem-sucedida! Reiniciando...");
                Serial.println("Atualizacao de firmware bem-sucedida! Reiniciando...");
                ESP.restart();
                // O ESP32 reiniciara automaticamente apos a conclusao do Update.end()
            }
            else
            {
                // Envia uma resposta de erro
                request->send(500, "text/plain", "Erro na atualizacao de firmware: ");
                Serial.println("Erro na atualizacao de firmware: ");
            }
        }, [] (AsyncWebServerRequest * request, String filename, size_t index, uint8_t * data, size_t len, bool final)
                    {
            // Callback para lidar com o processo de upload do arquivo
            if (!index)
            {
                // Inicio do upload
                Serial.printf("Iniciando upload de firmware: %s\n", filename.c_str());
                // UPDATE_SIZE_UNKNOWN e mais flexivel para uploads via POST
                if (!Update.begin(UPDATE_SIZE_UNKNOWN))
                {
                    Update.printError(Serial);
                    request->send(500, "text/plain", "Erro ao iniciar a atualizacao: ");
                }
            }

            // Escreve os dados recebidos na flash
            if (len)
            {
                if (Update.write(data, len) != len)
                {
                    Update.printError(Serial);
                    request->send(500, "text/plain", "Erro ao escrever na flash: ");
                }
            }

            // Fim do upload
            if (final)
            {
                if (Update.end(true))
                { // 'true' para reiniciar apos a atualizacao
                    Serial.println("Upload de firmware concluido e verificado. O ESP32 ira reiniciar.");
                }
                else
                {
                    Update.printError(Serial);
                    request->send(500, "text/plain", "Erro ao finalizar a atualizacao: ");
                }
            }
        });

        server.on("/update_fs", HTTP_POST, [](AsyncWebServerRequest * request) {
            request->send(200, "text/plain", (Update.hasError()) ? "Falha" : "Sucesso");
            ESP.restart();
        }, [] (AsyncWebServerRequest * request, String filename, size_t index, uint8_t * data,
                size_t len, bool final) {
            if (index == 0)
            {
                Serial.printf("Recebendo %s\n", filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_SPIFFS, 0x290000))
                {
                    Update.printError(Serial);
                }
            }
            if (Update.write(data, len) != len)
            {
                Update.printError(Serial);
            }
            if (final)
            {
                if (Update.end(true))
                {
                    Serial.println("Atualização do FS concluída");
                    ESP.restart();
                }
                else
                {
                    Update.printError(Serial);
                }
            }
        });

    }
};