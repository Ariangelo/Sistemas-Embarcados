#include <SoftwareSerial.h>

SoftwareSerial btSerial(4, 0); // RX, TX

void setup() {
  Serial.begin(9600);
  Serial.println("Informar o comando AT:");
  btSerial.begin(9600);
}

void loop()
{
  if (btSerial.available())
    Serial.write(btSerial.read());

  if (Serial.available())
    btSerial.write(Serial.read());
}
