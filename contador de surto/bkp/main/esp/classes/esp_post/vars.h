#include <WiFi.h>
#include <AsyncHTTPRequest_Generic.h>
AsyncHTTPRequest *request = new AsyncHTTPRequest();

extern String nome;
extern String rede;
extern String senha;
extern String url;

extern bool online;

bool posted = false;
extern bool need_post;

extern String api_status;
