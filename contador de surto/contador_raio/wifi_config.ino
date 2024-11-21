void wifi_config() {
  WiFi.begin(rede.c_str(), senha.c_str());
}

void reconnect_wifi() {
  const int reconnect_interval = 1000;
  static unsigned long current_reconnect_interval = 0;

  const int disconnect_timeout = 300000;
  static unsigned long current_disconnect_timeout = 0;

  if (WiFi.status() != WL_CONNECTED && millis() - current_reconnect_interval > reconnect_interval) {
    current_reconnect_interval = millis();
    Serial.println(F("Conectando ao WiFi..."));
    connected = false;
    if (millis() - current_disconnect_timeout > disconnect_timeout) {
      ESP.restart();
    }
    return;
  }

  if (WiFi.status() == WL_CONNECTED) {
    current_disconnect_timeout = millis();
    if (!connected) {
      Serial.println("conectado ao Wifi com sucesso");
      connected = true;
    }
  }
}
