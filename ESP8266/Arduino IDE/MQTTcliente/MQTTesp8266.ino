/*
  Exemplo básico de ESP8266 MQTT

  Este exemplo demonstra as funcionalidades básicas da biblioteca PubSubClient em combinação com o ESP8266.

  É realizada a conexão com um servidor MQTT e, em seguida:
  - publicação (publish) "mensagem MQTT = contador" para o tópico "Sitemas.Embarcados.Topico.Saida" a cada dois segundos.
  - subscreve (subscribe) o tópico "Sitemas.Embarcados.Topico.Entrada", imprimindo todas as mensagens recebe.
  - Se o primeiro caractere do tópico "Sistemas.Embarcados.Topico.Entrada" for 1, ligua o LED da placa NODEMCU, caso contrário desliga o LED.

  O sistema será reconectado ao servidor caso a conexão tenha sido perdida usando uma função conectaMQTT
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BUILTIN_LED  2

const char* ssid = "wirelessROBOTICA";
const char* senha = "********";

const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient clienteWIFI;
PubSubClient clienteMQTT(clienteWIFI);

// Metodo que monitora o recebimento de mensagens do broker MQTT
void callback(char* topico, byte* payload, unsigned int tamanho) {
  Serial.print("[MSG RECEBIDA] Topico: ");
  Serial.print(topico);
  Serial.print(" / Mensagem: ");
  for (int i = 0; i < tamanho; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Controla o LED conforme o valor recebido
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Liga o LED nivel baixo por saída ser PULL_UP
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Desliga o LED
  }
}

void conectaMQTT() {
  // Loop ate conexão
  while (!clienteMQTT.connected()) {
    Serial.print("Aguardando conexao MQTT...");
    if (clienteMQTT.connect("clienteWIFI" +  random(300))) {
      Serial.println("MQTT conectado");
      //faz subscribe automatico no topico
      clienteMQTT.subscribe("Sistemas.Embarcados.Topico.Entrada");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" tentando reconectar em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);

  Serial.begin(115200);

  // Conexao to Wi-Fi
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
  Serial.println(WiFi.RSSI());
  Serial.println("Use este endereço para conectar ao ESP8266");
  Serial.println();
  // Conexao com broker no servidor MQTT
  clienteMQTT.setServer(mqtt_server, 1883);
  // Definicao do procedimento de recebimento de mensagens
  clienteMQTT.setCallback(callback);
}

void loop() {
  if (!clienteMQTT.connected()) {
    conectaMQTT();
  }
  clienteMQTT.loop();
}
