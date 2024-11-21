void onRequestComplete(void *optParam, AsyncHTTPRequest *request, int readyState)
{
    if (readyState == 4)
    {
        Serial.println("Solicitação assíncrona concluída!");
        Serial.print("Código de resposta: ");
        int response_cd = request->responseHTTPcode();
        Serial.println(response_cd);

        Serial.print("Resposta do servidor: ");
        Serial.println(request->responseText());

        posted = false;
        need_post = false;

        api_status = response_cd == 200 ? "55" : "11";
    }
}

void make_post(String to_post)
{
    api_status = "50";
    Serial.println("MAKE POST: " + to_post);
    request->onReadyStateChange(onRequestComplete, NULL);
    if (request->open("POST", url.c_str()))
    {
        request->setReqHeader("Content-Type", "text/plain");
        request->send((const uint8_t *)to_post.c_str(), to_post.length());
        posted = true;
    }
    else
    {
        api_status = "12";
        Serial.println("Falha ao abrir a solicitação!");
    }
}