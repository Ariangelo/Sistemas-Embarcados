#define STBY  16  // D0
#define PWM_A 14  // D5
#define PWM_B 0   // D3
#define AI1 13    // D7
#define AI2 12    // D6
#define BI1 5     // D1
#define BI2 4     // D2

#define DIREITO  1
#define ESQUERDO 2
#define PARAR -1
#define FRENTE 0
#define VOLTAR 1

boolean infoCompleta = false;
char fimInformacao = '*';
int velocidade = 512;
int modo = PARAR;
int motor;

void setup() {
  Serial.begin(9600);

  pinMode(STBY, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);

  digitalWrite(STBY, HIGH);
}

void loop() {
  ESPserialEvent();
  switch (modo)
  {
    case FRENTE:
      frente(motor, velocidade);
      break;
    case VOLTAR:
      voltar(motor, velocidade);
      break;
    case PARAR:
      parar(motor);
      break;
  }
}

void frente(int motor, int velocidade) {
  if (motor == ESQUERDO) {
    analogWrite(PWM_A, velocidade);
    digitalWrite(AI1, HIGH);
    digitalWrite(AI2, LOW);
  } else {
    analogWrite(PWM_B, velocidade);
    digitalWrite(BI1, HIGH);
    digitalWrite(BI2, LOW);

  }
}

void voltar(int motor, int velocidade) {
  if (motor == ESQUERDO) {
    analogWrite(PWM_A, velocidade);
    digitalWrite(AI1, LOW);
    digitalWrite(AI2, HIGH);
  } else {
    analogWrite(PWM_B, velocidade);
    digitalWrite(BI1, LOW);
    digitalWrite(BI2, HIGH);
  }
}

void parar(int motor) {
  if (motor == ESQUERDO) {
    digitalWrite(AI1, LOW);
    digitalWrite(AI2, LOW);
  } else {
    digitalWrite(BI1, LOW);
    digitalWrite(BI2, LOW);
  }
}

void ESPserialEvent() {
  while (Serial.available()) {
    char c = Serial.read();
    switch (c)
    {
      case 'v':
        velocidade = map(Serial.parseInt(), 0, 100, 0, 1024);
        break;
      case 'f':
        modo = FRENTE;
        motor = Serial.parseInt();
        break;
      case 't':
        modo = VOLTAR;
        motor = Serial.parseInt();
        break;
      case 'p':
        modo = PARAR;
        motor = Serial.parseInt();
        break;
    }
    infoCompleta = (c == fimInformacao) || (c == '\n');
  }
}