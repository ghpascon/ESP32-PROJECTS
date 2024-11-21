void clear_commands()
{
    for (int i = 0; i < max_commands; i++)
        last_commands[i] = "";

    current_cmd = 0;
}

void add_command(String cmd)
{
    for (int i = 0; i < max_commands; i++)
    {
        if (last_commands[i] == "")
            break;

        if (last_commands[i] == cmd)
            return;
    }

    last_commands[current_cmd] = cmd;
    (current_cmd < max_commands) ? current_cmd++ : current_cmd = 0;
    Serial.println("TAG: " + cmd);
}

String get_json_commands()
{
    String json = "{\"tags\":[";

    for (int i = 0; i < max_commands; i++)
    {
        if (last_commands[i] == "")
            break;

        json += "\"" + last_commands[i] + "\",";
    }
    json += "]";
    json.replace(",]", "]");
    json.replace("\\", "");
    json += "}";
    return json;
}