#include "config.h"

char* client;
char* topic;

void callbackMQTT(char* topico, byte* payload, unsigned int tamanho) {
  String payloadMQTT = "";
  for (int i = 0; i < tamanho; i++) {
    payloadMQTT = payloadMQTT + (char)payload[i];
  }
  actions = createActions(MQTT, payloadMQTT);
}

int connectMQTT(PubSubClient &clienteMQTT) {
  int tentativas = 0;
  // Loop ate conexao
  Serial.print(tentativas + 1);
  Serial.print(" - Conectando MQTT ");
  while (!clienteMQTT.connect(client) && tentativas < 5) {
    delay(500);
    Serial.print(".");
    tentativas++;
  }
  if (clienteMQTT.connected()) {
    Serial.println(" MQTT conectado");
    clienteMQTT.subscribe(topic);
  } else {
    Serial.println(" Não foi possível conectar ao Broker MQTT.");
  }
  return clienteMQTT.connected() ? 0 : 1;
}

bool mqttConnect(PubSubClient &mqttClient, char* mqttServer, char* idClient, int mqttPort, char* mqttTopic) {
  client = idClient;
  topic = mqttTopic;

  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callbackMQTT);
  return connectMQTT(mqttClient);
}
