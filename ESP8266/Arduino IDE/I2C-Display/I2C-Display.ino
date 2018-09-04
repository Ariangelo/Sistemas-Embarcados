#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <SSD1306Wire.h>

#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define TAMANHO       GEOMETRY_128_32
#define TIME_ZONE    -3

// WiFi network info.
const char* ssid = "ssid";
const char* senha = "senha";

unsigned long contador;         // the debounce time; increase if the output flickers
unsigned long intervalo = 1000; // Tempo em ms do intervalo a ser utilizado

WiFiUDP ntpUDP; // Cliente UDP para o NTP
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000); // Configuracao do Cliente NTP
SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN, TAMANHO); // SDA, SCL -> Configuracao do display SSD1306

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

  horaCliente.begin();
  contador = millis();
}

void loop() {
  String infoDisplay;
  if (millis() - contador > intervalo) {
    horaCliente.update(); // Atualiza a hora no sistema utilizando o servidor NTP
    infoDisplay = horaCliente.getFormattedTime();
    // Mostra hora na porta Serial
    Serial.println(infoDisplay); // Imprime informacao formatada na serial
    // Mostra hora no display OLED
    display.clear();
    display.drawRect(0, 0, display.getWidth() - 1, display.getHeight() - 1);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_16);
    display.drawString(display.getWidth() / 2,  0, infoDisplay);
    display.setFont(ArialMT_Plain_10);
    display.drawString(display.getWidth() / 2, 16, "IP: " + WiFi.localIP().toString());
    display.display();
    contador = millis();
  }
}
