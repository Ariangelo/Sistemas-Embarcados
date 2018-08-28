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

    //Seta Baud Rate
    if (bluetoothData > 48 && bluetoothData < 57) { //valores '1' to '8'
      if (!acheiBaud) procuraBaudRate();
      btSerial.print("AT+BAUD" + String(bluetoothData - 48));
      delay(1500);
      if (btSerial.available()) Serial.println("Resposta = " + btSerial.readString());
      btSerial.end();
      baudInd = bluetoothData - 49;
      btSerial.begin(baudRates[baudInd]);
    }

    //Seta Novo nome ou Comando customizado
    if (bluetoothData == 'N' || bluetoothData == 'C') {
      String str = Serial.readString();
      if (bluetoothData == 'N') str = "AT+NAME" + str;
      if (!acheiBaud) procuraBaudRate();
      btSerial.print(str);
      delay(1500);
      if (btSerial.available()) Serial.println("Resposta = " + btSerial.readString());
    }

    //Setar Novo Pin
    if (bluetoothData == 'P') {
      int pin = Serial.parseInt();
      if (!acheiBaud) procuraBaudRate();
      btSerial.print("AT+PIN" + String(pin));
      delay(1500);
      if (btSerial.available()) Serial.println("Resposta = " + btSerial.readString());
    }
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
    delay(1500);
    if (btSerial.available()) {
      acheiBaud = true;
      Serial.println(btSerial.readString() + " em " + String(baudRates[baudInd]) + " Baud");
    }
    if (!acheiBaud) btSerial.end();
  }
  if (!acheiBaud) btSerial.begin(9600);
}

