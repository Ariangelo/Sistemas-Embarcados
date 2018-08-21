#include <SoftwareSerial.h>

#define PIN_RX        4
#define PIN_TX        0
#define PIN_FRENTE    12
#define PIN_TRAZ      13
#define PIN_ESQUERDA  14
#define PIN_DIREITA   15

int frenteLigado = LOW;
int trazLigado = LOW;
int esquerdaLigado = LOW;
int direitaLigado = LOW;

SoftwareSerial serial(PIN_RX, PIN_TX);

void setup()
{
  pinMode(PIN_FRENTE, OUTPUT);
  pinMode(PIN_TRAZ, OUTPUT);
  pinMode(PIN_ESQUERDA, OUTPUT);
  pinMode(PIN_DIREITA, OUTPUT);

  serial.begin(9600);
}

void loop()
{
  if (serial.available()) {
    char c = serial.read();
    if (c == '1') frenteLigado = HIGH;
    if (c == '3') trazLigado = HIGH;
    if (c == '4') esquerdaLigado = HIGH;
    if (c == '2') direitaLigado = HIGH;
    if (c == '0') {
      frenteLigado = LOW;
      trazLigado = LOW;
      esquerdaLigado = LOW;
      direitaLigado = LOW;
    }
  }
  digitalWrite(PIN_FRENTE, frenteLigado);
  digitalWrite(PIN_TRAZ, trazLigado);
  digitalWrite(PIN_ESQUERDA, esquerdaLigado);
  digitalWrite(PIN_DIREITA, direitaLigado);
}
