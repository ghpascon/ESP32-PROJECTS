class get_cmd
{
public:
    void show_config()
    {
        Serial.println();
        Serial.println("IP_0: " + String(ip_config[0][0]));
        Serial.println("IP_1: " + String(ip_config[1][0]));
        Serial.println("IP_2: " + String(ip_config[2][0]));
        Serial.println("IP_3: " + String(ip_config[3][0]));
        Serial.println();
        Serial.println("GATEWAY_0: " + String(ip_config[0][1]));
        Serial.println("GATEWAY_1: " + String(ip_config[1][1]));
        Serial.println("GATEWAY_2: " + String(ip_config[2][1]));
        Serial.println("GATEWAY_3: " + String(ip_config[3][1]));
        Serial.println();
        Serial.println("SUBNET_0: " + String(ip_config[0][2]));
        Serial.println("SUBNET_1: " + String(ip_config[1][2]));
        Serial.println("SUBNET_2: " + String(ip_config[2][2]));
        Serial.println("SUBNET_3: " + String(ip_config[3][2]));
        Serial.println();
        Serial.println("DNS_0: " + String(ip_config[0][3]));
        Serial.println("DNS_1: " + String(ip_config[1][3]));
        Serial.println("DNS_2: " + String(ip_config[2][3]));
        Serial.println("DNS_3: " + String(ip_config[3][3]));
        Serial.println();
        Serial.println("URL: " + url);
        Serial.println();
    }

    void get_ip(String cmd, int pos)
    {
        const String sep = ".";
        ip_config[0][pos] = cmd.substring(0, cmd.indexOf(sep)).toInt();
        cmd = cmd.substring(cmd.indexOf(sep) + 1);

        ip_config[1][pos] = cmd.substring(0, cmd.indexOf(sep)).toInt();
        cmd = cmd.substring(cmd.indexOf(sep) + 1);

        ip_config[2][pos] = cmd.substring(0, cmd.indexOf(sep)).toInt();
        ip_config[3][pos] = cmd.substring(cmd.indexOf(sep) + 1).toInt();
    }
};
