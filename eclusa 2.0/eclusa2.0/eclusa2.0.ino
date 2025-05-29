#include <neotimer.h>


int x1 = 0;
int z1 = 0;
int n1 = 0;
int l1 = 0;
int l2 = 0;

int x2 = 0;
int z2 = 0;
int n2 = 0;
int l3 = 0;
int l4 = 0;


int p1 = 0;
int p2 = 0;

int ae = 0;

int card[26] = {};
int decimal = 0;
int soma = 1;

String cmd = "";

int d0_w1 = 26;
int d1_w1 = 33;
int d0_w2 = 35;
int d1_w2 = 34;
int bt1 = 13;
int bt2 = 14;
int bte = 27;
int porta_fechada = 4;
int r700 = 18;
int emg = 19;
int p1_out = 22;
int p2_out = 23;
int porta_debounce_time = 0;

int read_time = 10000;
int current_read_time = 0;

Neotimer debounce;
Neotimer emerg;
Neotimer porta;


void wiegand_1() {
  if (digitalRead(d0_w1) == 1) {
    x1 = 0;
  }
  if (digitalRead(d0_w1) == 0 && x1 == 0) {
    n1 = n1 + 1;
    x1 = 1;
  }
  if (digitalRead(d1_w1) == 1) {
    z1 = 0;
  }
  if (digitalRead(d1_w1) == 0 && z1 == 0) {
    card[n1] = 1;
    n1 = n1 + 1;
    z1 = 1;
  }
}

void limpa_w1() {
  if (n1 != l1) {
    l1 = n1;
    l2 = 0;
  }
  if (n1 == l1) {
    l2 = l2 + 1;
  }
  if (l2 == 5000) {
    l1 = 0;
    l2 = 0;
    n1 = 0;
  }
}

void wiegand_2() {
  if (digitalRead(d0_w2) == 1) {
    x2 = 0;
  }
  if (digitalRead(d0_w2) == 0 && x2 == 0) {
    n2 = n2 + 1;
    x2 = 1;
  }
  if (digitalRead(d1_w2) == 1) {
    z2 = 0;
  }
  if (digitalRead(d1_w2) == 0 && z2 == 0) {
    card[n2] = 1;
    n2 = n2 + 1;
    z2 = 1;
  }
}

void limpa_w2() {
  if (n2 != l3) {
    l3 = n2;
    l4 = 0;
  }
  if (n2 == l3) {
    l4 = l4 + 1;
  }
  if (l4 == 5000) {
    l3 = 0;
    l4 = 0;
    n2 = 0;
  }
}

void decodifica_w1() {
  if (n1 == 26) {
    for (n1 = 24; n1 >= 9; n1--) {
      if (card[n1] == 1) {
        decimal = decimal + soma;
      }
      soma = soma * 2;
      card[n1] = 0;
    }
    Serial.println("#w1:"+String(decimal));

    n1 = 0;
    decimal = 0;
    soma = 1;
  }
}

void decodifica_w2() {
  if (n2 == 26) {
    for (n2 = 24; n2 >= 9; n2--) {
      if (card[n2] == 1) {
        decimal = decimal + soma;
      }
      soma = soma * 2;
      card[n2] = 0;
    }
    Serial.println("#w2:"+String(decimal));

    n2 = 0;
    decimal = 0;
    soma = 1;
  }
}

void botao_1() {
  if (digitalRead(bt1) == 0 && digitalRead(porta_fechada) == LOW) {
    abre_porta_1();
  }
}

void botao_2() {
  if (digitalRead(bt2) == 0 && digitalRead(porta_fechada) == LOW) {
    abre_porta_2();
  }
}

void emergencia() {
  if (digitalRead(bte) == HIGH) {
    if (ae == 0) {
      Serial.println("#emg:on");
      digitalWrite(emg, HIGH);
      digitalWrite(p1_out, LOW);
      digitalWrite(p2_out, LOW);
      ae = 1;
    }
  } else {
    if (ae == 1) {
      if (emerg.repeat()) {
        Serial.println("#emg:off");
        digitalWrite(emg, LOW);
        digitalWrite(p1_out, HIGH);
        digitalWrite(p2_out, HIGH);
        ae = 0;
      }
    }
  }
}

void verifica_serial() {
  if (Serial.available()) {
    cmd = Serial.readStringUntil('\n');
    if (cmd == "#open:1" && digitalRead(porta_fechada) == LOW) {
      abre_porta_1();
    }
    if (cmd == "#open:2" && digitalRead(porta_fechada) == LOW) {
      abre_porta_2();
    }
  }
}

void abre_porta_1() {
  Serial.println("#open:1");
  delay(200);
  digitalWrite(r700, HIGH);
  digitalWrite(p1_out, LOW);
  delay(2000);
  digitalWrite(p1_out, HIGH);
}

void abre_porta_2() {
  Serial.println("#open:2");
  delay(200);
  digitalWrite(r700, HIGH);
  digitalWrite(p2_out, LOW);
  delay(2000);
  digitalWrite(p2_out, HIGH);
}

void verifica_porta() {
  if (!digitalRead(porta_fechada) && millis() - porta_debounce_time > 300) {
    digitalWrite(r700, LOW);
  } else if (digitalRead(porta_fechada)) {
    porta_debounce_time = millis();
    current_read_time - millis();
    digitalWrite(r700, HIGH);
  } else if (millis() - current_read_time > read_time) {
    digitalWrite(r700, HIGH);
  }
}

void setup() {
  Serial.begin(115200);

  debounce.set(300);
  emerg.set(10000);
  porta.set(3000);
  pinMode(d0_w1, INPUT);
  pinMode(d1_w1, INPUT);
  pinMode(d0_w2, INPUT);
  pinMode(d1_w2, INPUT);
  pinMode(bt1, INPUT_PULLUP);
  pinMode(bt2, INPUT_PULLUP);
  pinMode(porta_fechada, INPUT_PULLUP);
  pinMode(r700, OUTPUT);
  pinMode(bte, INPUT_PULLUP);
  pinMode(emg, OUTPUT);
  pinMode(p1_out, OUTPUT);
  pinMode(p2_out, OUTPUT);

  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  digitalWrite(emg, LOW);
  digitalWrite(p1_out, HIGH);
  digitalWrite(p2_out, HIGH);
  digitalWrite(r700, HIGH);
}

void loop() {
  wiegand_1();
  limpa_w1();
  wiegand_2();
  limpa_w2();
  decodifica_w1();
  decodifica_w2();
  botao_1();
  botao_2();
  emergencia();
  verifica_serial();
  verifica_porta();
}