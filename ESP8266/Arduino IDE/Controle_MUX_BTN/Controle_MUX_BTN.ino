#define PIN_BOTAO1  0
#define pinoMUX     2
#define PIN_S0      12
#define PIN_S1      13
#define PIN_S2      14

int statusBotao;
int statusBotaoAnterior = LOW;
unsigned long debounceAnterior = 0;

int val[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH};

//Controle dos canais do multiplexador
int pins[3] = {PIN_S0, PIN_S1, PIN_S2};
void muxWrite(int canal) {
  for (int i = 0; i < 3; i++)  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], bitRead(canal, i));
    digitalWrite(pinoMUX, val[canal]);
  }
}

void setup() {
  pinMode(pinoMUX, OUTPUT);
}

void loop() {
  debounce(PIN_BOTAO1);
  for (int i = 0; i < 8; i++) {
    muxWrite(i);
    delay(1);
  }
}

void debounce(int b) {
  int leitura = digitalRead(b);
  if (leitura != statusBotaoAnterior) {
    debounceAnterior = millis();
  }
  if ((millis() - debounceAnterior) > 50) {
    if (leitura != statusBotao) {
      statusBotao = leitura;
      if (statusBotao == HIGH) {
        val[0] = !val[0];
      }
    }
  }
  statusBotaoAnterior = leitura;
}
