void check_signal() {
  const int debbounce_time = 300;
  static unsigned long current_debbounce_time = 0;
  static bool bt_pressed = false;

  if (millis() - current_debbounce_time < debbounce_time) return;

  if (!digitalRead(send_pin) && !bt_pressed) {
    current_debbounce_time = millis();
    display_post_response = "55";
    lightning_to_send++;
    bt_pressed = true;
    manut_status_ok=false;
  } else if (digitalRead(send_pin) && bt_pressed) {
    current_debbounce_time = millis();
    bt_pressed = false;
  }
}
