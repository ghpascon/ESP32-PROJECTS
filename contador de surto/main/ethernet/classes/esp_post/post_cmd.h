void make_post(String to_post)
{
    String post_url = url;
    post_url.replace("{name}", name);

    String post_Authorization = Authorization;
    post_Authorization.replace("{name}", name);

    Serial.println("MAKE POST: " + to_post);
    Serial.println(post_url);
    Serial.println(post_Authorization);

    http.begin(post_url);
    http.setTimeout(5000); 
    http.addHeader("Host", name);
    http.addHeader("Authorization", post_Authorization);

    int httpCode = http.POST(to_post);
    Serial.println("POSTED");

    if (httpCode > 0)
    {
        Serial.printf("HTTP Response code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_NO_CONTENT)
        { 
            Serial.println("Nenhuma resposta recebida.");
        }
        else
        {
            String payload = http.getString();
            Serial.println("Response: " + payload);
        }
    }
    else
    {
        Serial.printf("Falha ao abrir a solicitação! Código de erro: %d\n", httpCode);
    }
    http.end();
}
