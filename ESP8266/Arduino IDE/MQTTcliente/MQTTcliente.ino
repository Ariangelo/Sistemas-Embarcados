/*
  Exemplo básico de ESP8266 MQTT

  Este exemplo demonstra as funcionalidades básicas da biblioteca PubSubClient em combinação com o ESP8266.

  É realizada a conexão com um servidor MQTT e, em seguida:
  - publicação (publish) "mensagem MQTT = contador" para o tópico "Sitemas.Embarcados.Topico.Saida" a cada dois segundos.
  - subscreve (subscribe) o tópico "Sitemas.Embarcados.Topico.Entrada", imprimindo todas as mensagens recebe.
  - Se o primeiro caractere do tópico "Sitemas.Embarcados.Topico.Entrada" for 1, ligua o LED da placa NODEMCU, caso contrário desliga o LED.

  O sistema será reconectado ao servidor caso a conexão tenha sido perdida usando uma função conectaMQTT
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configuracoes iniciais
#define pinoBotao 0
#define pinoLED   BUILTIN_LED

typedef struct // Cria uma STRUCT para armazenar os dados dos botoes
{
  int pino;
  int canal = -1;
  int statusBotao;
  int statusBotaoAnterior = HIGH;
  unsigned long debounceAnterior = 0;
} Botao;

unsigned long tempoAnteriorDebounce = 0;
unsigned long debounceDelay = 50;   // tempo do debounce time; aumentar se saida oscila

const char* ssid = "wirelessROBOTICA";
const char* senha = "*********";

const char* mqtt_server = "broker.mqtt-dashboard.com";
const char* topico = "Sistemas.Embarcados.Topico.Entrada";

WiFiClient clienteWIFI;
PubSubClient clienteMQTT(clienteWIFI);
String strMacAddress;
char macAddress[6];

Botao botao;
int statusLED = HIGH;

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
    digitalWrite(pinoLED, LOW);   // Liga o LED nivel baixo por saída ser PULL_UP
  } else {
    digitalWrite(pinoLED, HIGH);  // Desliga o LED
  }
  statusLED = !digitalRead(pinoLED);
}

void conectaMQTT() {
  // Loop ate conexão
  while (!clienteMQTT.connected()) {
    Serial.print("Aguardando conexao MQTT...");
    if (clienteMQTT.connect(macAddress)) {
      Serial.println("MQTT conectado");
      //faz subscribe automatico no topico
      clienteMQTT.subscribe(topico);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(clienteMQTT.state());
      Serial.println(" tentando reconectar em 5 segundos.");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(pinoLED, OUTPUT);
  botao.pino = pinoBotao;
  pinMode(botao.pino, INPUT_PULLUP);

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
  strMacAddress = WiFi.macAddress();
  strMacAddress.toCharArray(macAddress,6);
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
  botao = debounce(botao);
}

Botao debounce(Botao b) {
  int leitura = digitalRead(b.pino);
  if (leitura != b.statusBotaoAnterior) {
    b.debounceAnterior = millis();
  }
  if ((millis() - b.debounceAnterior) > 50) {
    if (leitura != b.statusBotao) {
      b.statusBotao = leitura;
      if (b.statusBotao == HIGH) {
        statusLED = !statusLED;
        const char* payload = statusLED ? "1" : "0";
        clienteMQTT.publish(topico, payload);
      }
    }
  }
  b.statusBotaoAnterior = leitura;
  return b;
}
