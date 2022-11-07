#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
//para controlar estado do LED
#include <Ticker.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include <Adafruit_MPU6050.h>

#include <WiFiUdp.h>
#include <NTPClient.h>

#define OLED_RESET -1
#define ENDERECO_OLED 0x3C
#define DISPLAY_TAMANHO 128
#define DISPLAY_ALTURA 32

#define LED LED_BUILTIN
#define TIME_ZONE -3

Ticker ticker;
WiFiClient clienteWIFI;

String strMacAddress;
char macAddress[6];

unsigned long contador;          // Armazena o valor dos milisegundos até o próximo intervalo
unsigned long intervalo = 1000;  // Tempo em ms do intervalo a ser executado
float temperatura;
float umidade;
sensors_event_t a, g, temp;
bool relogio = true;
String payloadBT = "";  

Adafruit_MPU6050 mpu;
Adafruit_AM2320 am2320 = Adafruit_AM2320();                                    // Cria uma instancia do sensor AM2320
Adafruit_SSD1306 display(DISPLAY_TAMANHO, DISPLAY_ALTURA, &Wire, OLED_RESET);  // Configuracao do display SSD1306
WiFiUDP ntpUDP;                                                                // Cliente UDP (User Datagram Protocol) para o NTP (Network Time Protocol)
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000);        // Configuracao do Cliente NTP

void piscar() {
  digitalWrite(LED, !digitalRead(LED));
}

void configuracaoCallback(WiFiManager *gerenciadorWiFi) {
  Serial.println("Modo de configuração ativado");
  //Serial.println(WiFi.softAPIP());
  //Serial.println(gerenciadorWiFi->getConfigPortalSSID());
  //Modo de configuracao ativado led pisca rapido
  ticker.attach(0.2, piscar);
}

void setup() {
  Serial.begin(9600);
  if (!mpu.begin()) {
    Serial.println("Falha em ativar o sensor MPU6050");
    while (true) {
      delay(100);
    }
  }
  if (!display.begin(SSD1306_SWITCHCAPVCC, ENDERECO_OLED)) {
    Serial.println(F("SSD1306 falhou"));
    while (true) {
      delay(100);
    }
  }
  // Mostrar informacao no Display OLED
  mpu.getEvent(&a, &g, &temp);
  display.setRotation(a.acceleration.y > 0 ? 0 : 90);
  centralizaFonte("Conectando");
  // Mostrar informacao na porta Serial
  pinMode(0, INPUT);
  pinMode(LED, OUTPUT);
  // Forca o modo para STA+AP
  WiFi.mode(WIFI_STA);
  ticker.attach(0.6, piscar);
  //WiFiManager
  //Depois de configurado a primeira vez o acesso ao WiFi e automatico
  WiFiManager gerenciadorWiFi;
  //No caso de revogar o acesso ao WiFi
  //gerenciador.resetSettings();
  gerenciadorWiFi.setDebugOutput(false);
  gerenciadorWiFi.setAPCallback(configuracaoCallback);
  if (!gerenciadorWiFi.autoConnect("AutoConnectAP")) {
    Serial.println("Falha na conexão com a WiFi");
    //reseta o ESP e tenta novamente
    ESP.restart();
    delay(1000);
  }
  // Mostra IP do servidor
  Serial.println();
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Use este endereço para conectar ao dispositivo");
  Serial.println();
  strMacAddress = WiFi.macAddress();
  strMacAddress.toCharArray(macAddress, 6);
  centralizaNormal("IP: " + WiFi.localIP().toString(), 0.5);
  contador = millis();  // Inicializa o contador para o intervalo
  ticker.detach();
  //Mantem o LED ligado
  digitalWrite(LED, LOW);
  am2320.begin();
  horaCliente.begin();
  delay(2000);
}

void loop() {
  char infoDisplay[30];  // Variavel auxiliar para armazenar infoDisplay formatada

  if (Serial.available()) {
    serialBTevent();
  }

  mpu.getEvent(&a, &g, &temp);
  display.setRotation(a.acceleration.y > 0 ? 0 : 90);

  if (millis() - contador > intervalo) {
    if (relogio) {
      horaCliente.update();  // Atualiza a hora no sistema utilizando o servidor NTP
      horaCliente.getFormattedTime().toCharArray(infoDisplay, 30);
    } else {
      temperatura = am2320.readTemperature();                         // Obtem o valor de temperatura
      umidade = am2320.readHumidity();                                // Obtem o valor da umidade relativa
      sprintf(infoDisplay, "%.1f C - %.0f%%", temperatura, umidade);  // Formata a saida para ser mostrada no display
    }
    Serial.println(infoDisplay);   // Imprime informacao formatada na serial
    centralizaFonte(infoDisplay);  // Mostra informacao atualizada da hora no display OLED
    contador = millis();
  }
}

void serialBTevent() {
  while (Serial.available()) {
    char payload = (char)Serial.read();
    payloadBT += payload;
    if (payload == '\n') {
      payloadBT.trim();
      relogio = payloadBT == "1";
      payloadBT = "";
    }
  }
}

// Procedimentos para mostrar informacao no OLED
void centralizaFonte(String informacao) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSans9pt7b);
  display.clearDisplay();
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  display.getTextBounds(informacao, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((display.width() - w) / 2, display.height() - h + 2);
  display.print(informacao);
  display.display();
}

void centralizaNormal(String informacao, uint8_t escala) {
  int16_t x1, y1;
  uint16_t w, h;
  display.setFont();
  display.cp437(true);
  display.setTextSize(escala);
  display.clearDisplay();
  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);
  display.getTextBounds(informacao, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((display.width() - w) / 2, (display.height() - h) / 2);
  display.print(informacao);
  display.display();
}