void reset_in_config_mode() {
  const int reset_time = 5000;
  static unsigned long current_reset_time = 0;

  if (digitalRead(start_mode_pin)) current_reset_time = millis();

  if (millis() - current_reset_time > reset_time) ESP.restart();
}