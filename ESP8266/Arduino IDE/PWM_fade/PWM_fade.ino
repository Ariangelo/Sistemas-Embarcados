#define led 14

int brilho = 0;     // valor inicial para o brilho do LED
int valorFade = 1;  // valor de aumento do brilho do LED

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brilho);
  // atualiza o valor do brilho do LED:
  brilho = brilho + valorFade;
  // inverte a forma do fade:
  if (brilho == 0 || brilho == 255) {
    valorFade = -valorFade ;
  }
  // aguarda 30 milissegundos para ver o efeito de fade
  delay(30);
}
