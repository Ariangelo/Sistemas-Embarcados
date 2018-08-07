/*
  Botao

  Liga e desliga um LED conectado ao pino digital 2,
  ao pressionar um botão conectado ao pino 0.

  O circuito:
   - LED conectado do pino 2 ao terra
   - botão ligado do pino 0 a + 3.3V
   - resistor de 10k interligando do pino 0 ao terra

  Originalmente criado por
  DojoDave (2005) <http://www.0j0.org>
  Tom Igoe (2011)

  Este exemplo é de domínio público.
  http://www.arduino.cc/en/Tutorial/Button
*/

// Configuracoes iniciais
#define pinoBotao 0
#define pinoLED   2

void setup() {
  pinMode(pinoLED, OUTPUT);
  pinMode(pinoBotao, INPUT);
}

void loop() {
  digitalWrite(pinoLED, digitalRead(pinoBotao));
}
