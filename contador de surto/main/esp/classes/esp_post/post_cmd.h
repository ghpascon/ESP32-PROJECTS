void make_post(String to_post)
{
    api_status = "50";
    Serial.println("MAKE POST: " + to_post);

    http.begin(url);
    http.addHeader("Host", nome);
    http.addHeader("Authorization", Authorization);

    int httpCode = http.POST(to_post);

    if (httpCode > 0)
    {
        String payload = http.getString();
        Serial.printf("HTTP Response code: %d\n", httpCode);
        Serial.println("Response: " + payload);
    }
    else
    {
        Serial.println("Falha ao abrir a solicitação!");
        api_status = "12";
    }
    http.end();
}