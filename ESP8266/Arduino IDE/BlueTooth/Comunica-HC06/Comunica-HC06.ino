#include <SoftwareSerial.h>

#define PIN_RX        4
#define PIN_TX        0

SoftwareSerial btSerial(PIN_RX, PIN_TX);

long baudRates[] = {1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200};
int baudInd = 3;
char bluetoothData;
boolean acheiBaud = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    bluetoothData = Serial.read(); //Get next character from bluetooth
    if (bluetoothData == 'F') procuraBaudRate();
  }
}

void procuraBaudRate() {
  acheiBaud = false;
  baudInd = -1;
  while (!acheiBaud && baudInd < 8) {
    baudInd++;
    btSerial.begin(baudRates[baudInd]);
    Serial.println("Testando " + String(baudRates[baudInd]) + " Baud ...");
    delay(100);
    btSerial.print("AT");
    delay(500);
    if (btSerial.available()) {
      acheiBaud = true;
      Serial.println(btSerial.readString() + " em " + String(baudRates[baudInd]) + " Baud");
    }
    if (!acheiBaud) btSerial.end();
  }
  if (!acheiBaud) btSerial.begin(9600);
}
