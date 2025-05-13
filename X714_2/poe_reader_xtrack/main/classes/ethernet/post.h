void make_post(String xml)
{
    https.begin(client, url);
    https.addHeader("Content-Type", "application/xml");

    int httpResponseCode = https.POST(xml);

    if (httpResponseCode > 0)
    {
        Serial.println();
        Serial.print("Código de resposta: ");
        Serial.println(httpResponseCode);
        String response = https.getString();
        Serial.println("Resposta:");
        Serial.println(response);
        Serial.println();
    }
    else
    {
        Serial.print("Erro ao enviar POST: ");
        Serial.println(httpResponseCode);
    }

    https.end();
}

String get_tag_post(String epc, String ant)
{
    String upper_name = esp_name;
    upper_name.toUpperCase();
    String xml = "<msg>";
    xml += "<command>ReportRead</command>";
    xml += "<data>EVENT=";
    xml += "";
    xml += "|DEVICENAME=" + upper_name + "|ANTENNANAME=" + ant + "|TAGID=" + epc + "|</data>";
    xml += "<cmpl>STATE=APPEARED|DATA1=|DATA2=|DATA3=|DATA4=|DATA5=|</cmpl>";
    xml += "</msg>";

    Serial.println(xml);
    return xml;
}

static void post_task(void *pvParameters)
{
    Serial.println();
    Serial.println("Start posting tags");

    for (int i = 0; i < max_tags; i++)
    {
        if (tags_to_post[i][0] == "")
            break;
        make_post(get_tag_post(tags_to_post[i][0], tags_to_post[i][1]));
        tags_to_post[i][0] = "";
    }

    posted = false;

    Serial.println("Complete");
    Serial.println();

    vTaskDelete(NULL); // Finaliza a tarefa
}

void create_post_tag()
{
    xTaskCreatePinnedToCore(
        post_task,                 // Função da tarefa
        "Task_without_parameters", // Nome da tarefa
        16384,                     // Tamanho da pilha
        NULL,                      // Parâmetros para a tarefa
        1,                         // Prioridade da tarefa
        NULL,                      // Handle da tarefa
        1                          // Núcleo (Core 1)
    );
}
