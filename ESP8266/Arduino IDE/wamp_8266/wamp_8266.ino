#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Configuracoes iniciais
#define pinoBotao     0

const char* ssid = "ssid";
const char* password = "senha";

const char* host = "app-votar.herokuapp.com"; // Servidor - Roteador dos procedimentos publicados
const int httpPort = 80; // Porta do servidor
const String url = "/call"; // Caminho do webservice dos procedimentos publicados

WiFiClient client; // Cliente WIFI

void setup() {
  pinMode(pinoBotao, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Conectando com ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectada");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Conectado ao servidor: ");
  Serial.println(host);
}

void loop() {
  if (digitalRead(pinoBotao) == LOW) {
    if (!client.connect(host, httpPort)) {
      Serial.println("Conexão falhou");
      return;
    }
    Serial.print("URL requisitada: ");
    Serial.println(url);
    // Informacao no formato JSON para comunicacao com o servidor de procedimentos
    // {"procedure": "io.crossbar.demo.voto.votar", "args": ["c3po"]}
    //String data = "{\"procedure\": \"io.crossbar.demo.voto.votar\", \"args\": [ \"c3po\"]}"; // Votar no C3PO
    //String data = "{\"procedure\": \"io.crossbar.demo.voto.votar\", \"args\": [ \"bb8\"]}"; // Votar no BB8
    String data = "{\"procedure\": \"io.crossbar.demo.voto.votar\", \"args\": [ \"r2d2\"]}"; // Votar no R2D2
    // Requisicao postada no servidor
    client.print("POST " + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Content-Type: application/json" + "\r\n" +
                 "Content-Length: " + data.length() + "\r\n\r\n" +
                 data);
    delay(200); // Tempo para garantir conexao
  }
}
