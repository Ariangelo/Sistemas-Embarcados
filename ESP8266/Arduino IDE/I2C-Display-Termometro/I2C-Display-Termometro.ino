#include <ESP8266WiFi.h>
#include <SSD1306Wire.h>
#include <AM2320.h>

#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define TAMANHO       GEOMETRY_128_32

// WiFi network info.
const char* ssid = "ssid";
const char* senha = "senha";

unsigned long contador;         // Armazena o valor dos milisegundos até o próximo intervalo
unsigned long intervalo = 1000; // Tempo em ms do intervalo a ser executado
float temperatura;
float umidade;

SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306
AM2320 sensor; // Cria uma instancia do sensor AM2320

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
  Serial.print("Conectando ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Mostra IP da conexao na porta Serial
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Use este endereço para conectar ao ESP8266");
  Serial.println();
  // Mostra o IP da conexao no display OLED
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.drawString(display.getWidth() / 2, 18, "IP: " + WiFi.localIP().toString());
  display.display();

  sensor.begin(SDA_PIN, SCL_PIN); // Conecta o sensor AM2320 ao barramento I2C - SDA, SCL
  contador = millis(); // Inicializa o contador para o intervalo
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
