#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SSD1306Wire.h>
#include <AM2320.h>

#define PIN_BOTAO1    0
#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define TAMANHO       GEOMETRY_128_32
#define TIME_ZONE    -3

// WiFi network info.
const char* ssid = "ssid";
const char* senha = "senha";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "xxxxxxx";
char password[] = "xxxxxxx";
char clientID[] = "xxxxxxx";

// Configuracao do botao de controle da informacao do display
int statusBotao;
int statusBotaoAnterior = LOW;
int leituraBotao;
unsigned long debounceAnterior = 0;

unsigned long contador;       // the debounce time; increase if the output flickers
unsigned long intervalo = 10; // Tempo em ms do intervalo a ser executado
float temperatura;
float umidade;

WiFiUDP ntpUDP; // Cliente UDP para o NTP
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000); // Configuracao do Cliente NTP
SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306
AM2320 sensor; // Create an instance of sensor

void setup() {
  pinMode(PIN_BOTAO1, INPUT_PULLUP);

  // Conexao to Wi-Fi
  display.init();
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
  
  Cayenne.begin(username, password, clientID);
}

void loop() {
  String infoDisplay;
  char strDisplay[30];

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
  display.clear();
  display.drawRect(0, 0, display.getWidth() - 1, display.getHeight() - 1);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 - 16, infoDisplay);
  display.setFont(ArialMT_Plain_10);
  display.drawString(display.getWidth() / 2, display.getHeight() / 2 + (TAMANHO == GEOMETRY_128_64 ? 5 : 0), "IP: " + WiFi.localIP().toString());
  display.display();

  contador = millis();

  Cayenne.loop();
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

CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(1, temperatura, "Temperatura", "C");
  Cayenne.virtualWrite(2, umidade, "Umidade", "%");
}

CAYENNE_IN(PIN_BOTAO1) {
  leituraBotao = !leituraBotao;
}
