#define led 14

int brilho = 0; 
int valorFade = 1;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, brilho);
  brilho = brilho + valorFade;
  if (brilho == 0 || brilho == 255) {
    valorFade = -valorFade ;
  }
  delay(30);
}
