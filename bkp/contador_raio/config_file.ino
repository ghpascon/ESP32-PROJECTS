String config_file = "/config.txt";

void salvar_config() {
  clearFile();
  writeFile("nome:" + nome);
  writeFile("rede:" + rede);
  writeFile("senha:" + senha);
  writeFile("api:" + api);
  writeFile("lightning_to_send:" + String(lightning_to_send));
}

void save_parameter(String parameter) {
  if (parameter.startsWith("nome:")) {
    parameter.replace("nome:", "");
    nome = parameter;
  }

  else if (parameter.startsWith("rede:")) {
    parameter.replace("rede:", "");
    rede = parameter;
  }

  else if (parameter.startsWith("senha:")) {
    parameter.replace("senha:", "");
    senha = parameter;
  }

  else if (parameter.startsWith("api:")) {
    parameter.replace("api:", "");
    api = parameter;
  }

  else if (parameter.startsWith("lightning_to_send:")) {
    parameter.replace("lightning_to_send:", "");
    lightning_to_send = parameter.toInt();
  }
}

void readFile() {
  File file_config = LittleFS.open(config_file, "r");

  if (!file_config) {
    Serial.println("Falha ao abrir o arquivo para leitura");
    return;
  }

  Serial.println("Conteúdo do arquivo:");
  while (file_config.available()) {
    String line = file_config.readStringUntil('\n');
    line.replace(" ", "");
    line.replace("\r", "");
    line.replace("\n", "");
    Serial.println(line);
    save_parameter(line);
  }

  file_config.close();
}

void writeFile(String to_write) {
  File file_config = LittleFS.open(config_file, "a");
  if (!file_config) {
    Serial.println("Falha ao abrir o arquivo para escrita");
    return;
  }

  file_config.print("\n" + to_write);
  file_config.close();

  Serial.println("Escrita concluída: '" + to_write + "' foi adicionado ao arquivo");
}

void clearFile() {
  File file_config = LittleFS.open(config_file, "w");  // Abre o arquivo em modo de escrita (trunca o arquivo)

  if (!file_config) {
    Serial.println("Falha ao abrir o arquivo para limpar");
    return;
  }

  file_config.close();

  Serial.println("Arquivo limpo com sucesso");
}