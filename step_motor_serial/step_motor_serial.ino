// Motor pins
#define PUL_X 42
#define DIR_X 41
#define PUL_Y 40
#define DIR_Y 39

// Step pulse interval (µs)
#define PULSE_INTERVAL 500

struct Motor {
  int pinPul;
  int pinDir;
  long stepsTarget;
  long stepsDone;
  unsigned long lastPulse;
  unsigned int pulseInterval;
  bool pulseState;
  char axis;
};

Motor motorX = { PUL_X, DIR_X, 0, 0, 0, PULSE_INTERVAL, false, 'X' };
Motor motorY = { PUL_Y, DIR_Y, 0, 0, 0, PULSE_INTERVAL, false, 'Y' };

void setup() {
  Serial.begin(115200);

  pinMode(motorX.pinPul, OUTPUT);
  pinMode(motorX.pinDir, OUTPUT);
  pinMode(motorY.pinPul, OUTPUT);
  pinMode(motorY.pinDir, OUTPUT);
}

void loop() {
  check_serial();
  updateMotor(motorX);
  updateMotor(motorY);
}

void check_serial() {
  if (!Serial.available()) return;

  String cmd = Serial.readStringUntil('\n');
  cmd.trim();
  cmd.toLowerCase();

  if (cmd.startsWith("x:")) {
    int steps = cmd.substring(2).toInt();
    prepareMove(motorX, steps);
  } else if (cmd.startsWith("y:")) {
    int steps = cmd.substring(2).toInt();
    prepareMove(motorY, steps);
  } else {
    Serial.println("[WARN] Unknown command!");
  }
}

void prepareMove(Motor &m, int steps) {
  if (steps == 0) return;

  Serial.println(String(m.axis) + " -> " + String(steps));

  if (steps > 0) {
    digitalWrite(m.pinDir, HIGH);
  } else {
    digitalWrite(m.pinDir, LOW);
    steps = -steps;
  }

  m.stepsTarget = steps;
  m.stepsDone = 0;
  m.lastPulse = micros();
  m.pulseState = false;
}

void updateMotor(Motor &m) {
  if (m.stepsDone >= m.stepsTarget) return;

  unsigned long now = micros();
  if (now - m.lastPulse >= m.pulseInterval) {
    m.lastPulse = now;
    m.pulseState = !m.pulseState;
    digitalWrite(m.pinPul, m.pulseState);

    if (!m.pulseState) {
      m.stepsDone++;
      if (m.stepsDone >= m.stepsTarget) {
        Serial.println("ok");
      }
    }
  }
}
