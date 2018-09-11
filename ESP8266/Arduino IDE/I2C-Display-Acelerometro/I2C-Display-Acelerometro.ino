#include <ESP8266WiFi.h>
#include <SSD1306Wire.h>
#include <Wire.h>

#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define ENDERECO_MPU  0x68
#define TAMANHO       GEOMETRY_128_32
#define TIME_ZONE    -3

// WiFi network info.
const char* ssid = "MyASUS";
const char* senha = "9a4281138522";

unsigned long contador;    // the debounce time; increase if the output flickers
unsigned long intervalo = 1000;     // Tempo em ms do intervalo a ser executado

SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306

//Variaveis para armazenar valores dos sensores
int acX, acY, acZ, gyX, gyY, gyZ;
signed int temp;

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.beginTransmission(ENDERECO_MPU);
  Wire.write(0x6B);
  //Inicializa o MPU-6050
  Wire.write(0);
  Wire.endTransmission(true);

  // Conexao to Wi-Fi
  display.init();
  if (lePosicao()) display.flipScreenVertically();
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.setFont(ArialMT_Plain_24);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2, "Conectando");
  display.display();

  Serial.begin(115200);
  Serial.print("Conectando ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Mostra IP do servidor
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Use este endereço para conectar ao ESP8266");
  Serial.println();

  // Mostra o IP da conexao no display OLED
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2, "IP: " + WiFi.localIP().toString());
  display.display();

  contador = millis();
}

void loop() {
  String infoDisplay;
  char strDisplay[30];

  if (millis() - contador > intervalo) {
    sprintf(strDisplay, "%.1fºC", lePosicao()); // Formata a saida para ser mostrada no display
    infoDisplay = strDisplay; // Atualiza o conteudo da informacao para String infoDisplay

    Serial.println(infoDisplay); // Imprime informacao formatada na serial

    display.clear();
    display.drawRect(0, 0, display.getWidth() - 1, display.getHeight() - 1);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 16, infoDisplay);
    display.setFont(ArialMT_Plain_10);
    display.drawString(display.getWidth() / 2, display.getHeight() / 2 + (TAMANHO == GEOMETRY_128_64 ? 5 : 0), "IP: " + WiFi.localIP().toString());
    display.display();

    contador = millis();
  }
}

float lePosicao() {
  Wire.beginTransmission(ENDERECO_MPU);
  Wire.write(0x3B);  // inicia com o registro 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(ENDERECO_MPU, 14, 1);
  //Armazena o valor dos sensores nas variaveis correspondentes
  acX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  acY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  acZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  temp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  gyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  gyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  gyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  acX = map(acX, 0, 65535, 0, 200);
  acY = map(acY, 0, 65535, 0, 200);
  acZ = map(acZ, 0, 65535, 0, 200);

  temp = temp / 340 + 36.53;

  gyX = map(gyX, 0, 65535, 0, 200);
  gyY = map(gyY, 0, 65535, 0, 200);
  gyZ = map(gyZ, 0, 65535, 0, 200);

  return temp;
}
