void onRequestComplete(void *optParam, AsyncHTTPRequest *request, int readyState)
{
    if (readyState == 4)
    {
        Serial.println("Solicitação assíncrona concluída!");
        Serial.print("Código de resposta: ");
        Serial.println(request->responseHTTPcode());

        Serial.print("Resposta do servidor: ");
        Serial.println(request->responseText());

        posted = false;
    }
}

void make_post(String to_post)
{
    request->onReadyStateChange(onRequestComplete, NULL);
    if (request->open("POST", url.c_str()))
    {
        request->setReqHeader("Content-Type", "text/plain");
        request->send((const uint8_t *)to_post.c_str(), to_post.length());
        posted = true;
        clear_commands();
    }
    else
    {
        Serial.println("Falha ao abrir a solicitação!");
    }
}