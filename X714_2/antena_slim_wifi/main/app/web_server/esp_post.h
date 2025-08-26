void make_post(String json)
{
    HTTPClient http;

    http.begin(wifi_url);
    http.setTimeout(5000);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(json);

    Serial.print("Response code: ");
    Serial.println(httpResponseCode);
    Serial.println(http.getString());

    http.end();
}

void post_tags()
{
    const int time = 10000;
    static unsigned long current_time = millis();

    if (millis() - current_time < time || !is_connected)
        return;

    current_time = millis();
    Serial.println("Start posting...");

    String payload = "";
    if (current_tag == 0)
    {
        payload = "{";
        payload += "\"device\":\"" + wifi_name + "\",";
        payload += "\"event_type\":\"keep_alive\",";
        payload += "\"event_data\":{}";
        payload += "}";
        make_post(payload);
        Serial.println("End posting");
        return;
    }

    payload = "[";

    bool has_tags = false;

    for (int i = 0; i < max_tags; i++)
    {
        if (tags[i].epc == "")
            continue;

        has_tags = true;

        payload += "{";
        payload += "\"device\":\"" + wifi_name + "\",";
        payload += "\"event_type\":\"tag\",";
        payload += "\"event_data\":{";
        payload += "\"device\":\"" + wifi_name + "\",";
        payload += "\"epc\":\"" + tags[i].epc + "\",";
        payload += "\"tid\":\"" + tags[i].tid + "\",";
        payload += "\"ant\":" + String(tags[i].ant_number) + ",";
        payload += "\"rssi\":" + String(tags[i].rssi);
        payload += "}},";
    }

    if (has_tags)
    {
        if (payload.endsWith(","))
        {
            payload.remove(payload.length() - 1);
        }
        payload += "]";
    }
    else
    {
        payload = "[]";
    }

    make_post(payload);
    tag_commands.clear_tags();
    Serial.println("End posting");
}