#include <Wire.h>
#include <Adafruit_SSD1306.h>

//Endereco I2C do MPU6050
const int MPU = 0x68;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

//Variaveis para armazenar valores dos sensores
int16_t rawAcX, rawAcY, rawAcZ, Tmp, rawGyX, rawGyY, rawGyZ;
float acX, acY, acZ, gyroX, gyroY, gyroZ;

void setup() {
  Serial.begin(115200);
  Wire.begin();  //21, 22, 400000);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);

  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  //Solicita os dados do sensor
  Wire.requestFrom(MPU, 14, 1);

  //Armazena o valor dos sensores nas variaveis correspondentes

  rawAcX = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  rawAcY = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  rawAcZ = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read();     //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  rawGyX = Wire.read() << 8 | Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  rawGyY = Wire.read() << 8 | Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  rawGyZ = Wire.read() << 8 | Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  acX = ((float)rawAcX) / 16384;
  acY = ((float)rawAcY) / 16384;
  acZ = ((float)rawAcZ) / 16384;

  gyroX = ((float)rawGyX) / 131;
  gyroY = ((float)rawGyY) / 131;
  gyroZ = ((float)rawGyZ) / 131;

  //Mostra os valores na serial
  Serial.print("Acel. X = ");
  Serial.print(acX);
  Serial.print(" | Y = ");
  Serial.print(acY);
  Serial.print(" | Z = ");
  Serial.print(acZ);
  Serial.print(" | Gir. X = ");
  Serial.print(gyroX);
  Serial.print(" | Y = ");
  Serial.print(gyroY);
  Serial.print(" | Z = ");
  Serial.print(gyroZ);
  Serial.print(" | Temp = ");
  Serial.println(Tmp / 340.00 + 36.53);

  display.clearDisplay();
  display.setRotation(acY > 0 ? 0 : 90);
  display.setCursor(0, 0);

  display.println("Acelerometro - G");
  display.print(acX, 2);
  display.print(", ");
  display.print(acY, 2);
  display.print(", ");
  display.print(acZ, 2);
  display.println("");

  display.println("Giroscopio - rps");
  display.print(gyroX, 1);
  display.print(", ");
  display.print(gyroY, 1);
  display.print(", ");
  display.print(gyroZ, 1);
  display.println("");

  display.display();

  //Aguarda 300 ms e reinicia o processo
  delay(300);
}
