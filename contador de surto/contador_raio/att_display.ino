void att_display() {
  const int att_display_time = 500;
  static unsigned long current_att_display_time = 0;

  if (millis() - current_att_display_time < att_display_time) return;
  current_att_display_time = millis();
  spr.setFreeFont(&FreeSansBold12pt7b);

  String txt;
  int display_font;

  txt = "EMBRASTEC";
  display_font = 2;
  spr.setTextSize(display_font);

  spr.createSprite(spr.textWidth(txt), spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(0xffc0, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite((SCREEN_WIDTH / 2) - (spr.textWidth(txt) / 2), 5);
  spr.deleteSprite();

  if (config_mode) {
    txt = "CONFIG MODE";
    display_font = 1;
    spr.setTextSize(display_font);

    spr.createSprite(spr.textWidth(txt) + 50, spr.fontHeight());
    spr.setColorDepth(16);
    spr.fillSprite(0x0000);
    spr.setTextColor(0xffc0, 0x0000);

    spr.drawString(txt, 0, 0);
    spr.pushSprite(10, 60);
    spr.deleteSprite();

    txt = "TEMPO RESTANTE: ";
    display_font = 1;
    spr.setTextSize(display_font);

    spr.createSprite(spr.textWidth(txt) + 50, spr.fontHeight());
    spr.setColorDepth(16);
    spr.fillSprite(0x0000);
    spr.setTextColor(0xffff, 0x0000);

    spr.drawString(txt, 0, 0);
    spr.pushSprite(10, 110);
    spr.deleteSprite();

    txt = String((reset_config_time - millis()) / 1000);
    display_font = 1;
    spr.setTextSize(display_font);

    spr.createSprite(spr.textWidth(txt) + 50, spr.fontHeight());
    spr.setColorDepth(16);
    spr.fillSprite(0x0000);
    spr.setTextColor(0xffff, 0x0000);

    spr.drawString(txt, 0, 0);
    spr.pushSprite(10, 150);
    spr.deleteSprite();
    return;
  }

  txt = connected ? "ONLINE" : "OFFLINE";
  display_font = 1;
  spr.setTextSize(display_font);

  spr.createSprite(spr.textWidth(txt) + 50, spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(connected ? 0x07e0 : 0xf800, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite(10, 60);
  spr.deleteSprite();

  txt = "Status da API:";
  display_font = 1;
  spr.setTextSize(display_font);

  spr.createSprite(spr.textWidth(txt) + 50, spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(0xffff, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite(10, 100);
  spr.deleteSprite();

  txt = display_post_response;
  display_font = 1;
  spr.setTextSize(display_font);

  spr.createSprite(SCREEN_WIDTH, spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(0xffff, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite(10, 135);
  spr.deleteSprite();

  txt = "Total de Surtos: " + String(total_lightning);
  display_font = 1;
  spr.setTextSize(display_font);

  spr.createSprite(SCREEN_WIDTH, spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(0xffff, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite(10, 170);
  spr.deleteSprite();

  spr.setFreeFont(&FreeSans9pt7b);

  txt = "Surge Counter V.1";
  display_font = 1;
  spr.setTextSize(display_font);

  spr.createSprite(SCREEN_WIDTH, spr.fontHeight());
  spr.setColorDepth(16);
  spr.fillSprite(0x0000);
  spr.setTextColor(0xffff, 0x0000);

  spr.drawString(txt, 0, 0);
  spr.pushSprite(150, 210);
  spr.deleteSprite();
}