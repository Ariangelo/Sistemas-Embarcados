#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SSD1306Wire.h>
#include <AM2320.h>
#include <Wire.h>

#define PIN_BOTAO1    0
#define PIN_FRENTE    12
#define PIN_TRAZ      13
#define PIN_ESQUERDA  14
#define PIN_DIREITA   15
#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define ENDERECO_MPU  0x68
#define TAMANHO       GEOMETRY_128_32
#define TIME_ZONE    -3

// WiFi network info.
const char* ssid = "seuSSID";
const char* senha = "suaSenha";

int statusBotao;
int statusBotaoAnterior = LOW;
int leituraBotao;
unsigned long debounceAnterior = 0;
unsigned long contador;    
unsigned long intervalo = 10;     // Tempo em ms do intervalo a ser executado
float temperatura;
float umidade;

WiFiUDP ntpUDP; // Cliente UDP para o NTP
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000); // Configuracao do Cliente NTP
SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306
AM2320 sensor; // Create an instance of sensor

bool mudouDirecao, mudouDirecaoAnterior;
//Variaveis para armazenar valores dos sensores
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
  pinMode(PIN_BOTAO1, INPUT_PULLUP);
  pinMode(PIN_FRENTE, OUTPUT);
  pinMode(PIN_TRAZ, OUTPUT);
  pinMode(PIN_ESQUERDA, OUTPUT);
  pinMode(PIN_DIREITA, OUTPUT);

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

  horaCliente.begin();
  sensor.begin(SDA_PIN, SCL_PIN);
  contador = millis();

}

void loop() {
  String infoDisplay;
  char strDisplay[30];

  mudouDirecao = lePosicao();
  debounce(PIN_BOTAO1);
  if (millis() - contador > intervalo) {
    horaCliente.update(); // Atualiza a hora no sistema utilizando o servidor NTP
    if (sensor.measure()) {
      temperatura = sensor.getTemperature();
      umidade = sensor.getHumidity();
      sprintf(strDisplay, "%.1fºC  -  %.0f%%", temperatura, umidade);
    } else {
      int erroSensor = sensor.getErrorCode();
      switch (erroSensor) {
        case 1:
          infoDisplay = "Sensor não conectado";
          break;
        case 2:
          infoDisplay = "Dado sensor inválido";
          break;
      }
    }
    if (leituraBotao == HIGH) {
      infoDisplay = horaCliente.getFormattedTime();
    } else {
      infoDisplay = strDisplay;
    }
  }
  Serial.println(infoDisplay); // Imprime informacao formatada na serial
  // Mostra informacao atualizada da hora no display OLED
  if (mudouDirecao != mudouDirecaoAnterior) {
    if (mudouDirecao) {
      display.init();
      display.flipScreenVertically();
    } else {
      display.init();
    }
    mudouDirecaoAnterior = mudouDirecao;
  }
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

bool lePosicao() {
  Wire.beginTransmission(ENDERECO_MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(ENDERECO_MPU, 14, 1);
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX = Wire.read() << 8 | Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp = Wire.read() << 8 | Wire.read(); //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX = Wire.read() << 8 | Wire.read(); //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  AcX = map(AcX, 0, 65535, 0, 200);
  AcY = map(AcY, 0, 65535, 0, 200);
  AcZ = map(AcZ, 0, 65535, 0, 200);

  GyX = map(GyX, 0, 65535, 0, 200);
  GyY = map(GyY, 0, 65535, 0, 200);
  GyZ = map(GyZ, 0, 65535, 0, 200);

  return AcY > 145;
}

void debounce(int b) {
  int leitura = digitalRead(b);
  if (leitura != statusBotaoAnterior) {
    debounceAnterior = millis();
  }
  if ((millis() - debounceAnterior) > 50) {
    if (leitura != statusBotao) {
      statusBotao = leitura;
      if (statusBotao == HIGH) {
        leituraBotao = !leituraBotao;
      }
    }
  }
  statusBotaoAnterior = leitura;
}
