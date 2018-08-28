/*
  Blink

  Liga um LED por um segundo, depois desliga por um segundo, repetidamente.

  O circuito:
   - LED conectado do pino 2 ao terra

  Originalmente criado por
  Scott Fitzgerald (2014)
  Arturo Guadalupi (2016)
  Colby Newman (2016)

  Este exemplo é de domínio público.
  http://www.arduino.cc/en/Tutorial/Blink
*/

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
