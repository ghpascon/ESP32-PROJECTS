#include <WiFi.h>
#include <HTTPClient.h>
HTTPClient http;

extern String nome;
extern String rede;
extern String senha;
extern String url;

extern bool online;

bool posted = false;
extern bool need_post;

extern String api_status;
extern String Authorization;
