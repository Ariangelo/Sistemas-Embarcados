#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
//para controlar estado do LED
#include <Ticker.h>

#include <SSD1306Wire.h>
#include <AM2320.h>

#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define TAMANHO       GEOMETRY_128_32
#define LED LED_BUILTIN

Ticker ticker;
WiFiClient clienteWIFI;

String strMacAddress;
char macAddress[6];

unsigned long contador;         // Armazena o valor dos milisegundos até o próximo intervalo
unsigned long intervalo = 1000; // Tempo em ms do intervalo a ser executado
float temperatura;
float umidade;

AM2320 sensor; // Cria uma instancia do sensor AM2320
SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306

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
  // Conexao to Wi-Fi
  // Mostrar informacao no Display OLED
  display.init();
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.setFont(ArialMT_Plain_24);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2, "Conectando");
  display.display();
  // Mostrar informacao na porta Serial
  Serial.begin(115200);
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

  // Mostra o IP da conexao no display OLED
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(display.getWidth() / 2, 18, "IP: " + WiFi.localIP().toString());
  display.display();

  contador = millis(); // Inicializa o contador para o intervalo

  ticker.detach();
  //Mantem o LED ligado
  digitalWrite(LED, LOW);
  
  sensor.begin();//(SDA_PIN, SCL_PIN); // Conecta o sensor AM2320 ao barramento I2C - SDA, SCL
}

void loop() {
  String infoDisplay; // Variavel que armazena a informacao a ser mostrada no display ou porta serial
  char strDisplay[30]; // Variavel auxiliar para armazenar infoDisplay formatada
  if (millis() - contador > intervalo) {
    if (sensor.measure()) { // Verifica se o sensor esta operacional para leitura dos valores
      temperatura = sensor.getTemperature(); // Obtem o valor de temperatura
      umidade = sensor.getHumidity(); // Obtem o valor da umidade relativa
      sprintf(strDisplay, "%.1fºC  -  %.0f%%", temperatura, umidade); // Formata a saida para ser mostrada no display
    } else {
      sprintf(strDisplay, "Erro leitura");
      int errorCode = sensor.getErrorCode();
      switch (errorCode) {
        case 1: Serial.println("ERR: Sensor is offline"); break;
        case 2: Serial.println("ERR: CRC validation failed."); break;
      }
    }

    infoDisplay = strDisplay; // Atualiza o conteudo da informacao para String infoDisplay
    Serial.println(infoDisplay); // Imprime informacao formatada na serial
    // Mostra informacao atualizada da hora no display OLED
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
