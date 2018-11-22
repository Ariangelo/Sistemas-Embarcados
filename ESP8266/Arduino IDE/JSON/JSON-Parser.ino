// ArduinoJson - arduinojson.org
// Exemplo de como utilizar JSON com ArduinoJson.
// https://arduinojson.org/v6/example/parser/ para mais detalhes

#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  // Alocacao de espaco para o documento JSON
  // 200 é o tamanho em bytes que será alocado na memoria
  // Use arduinojson.org/assistant para computar a capacidade
  StaticJsonDocument<200> doc;

  // JSON string de informacoes.
  // Usar char[] como mostrado
  char json[] = "{\"sensor\":\"AM2320\",\"hora\":\"23:59:59\",\"info\":[28.75, 72.30]}";

  // Deserializar o documento JSON
  DeserializationError erro = deserializeJson(doc, json);

  // Verificacao se nao houve erro
  if (erro) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(erro.c_str());
    return;
  } else {
    // Obtem o root do docuemento JSON
    JsonObject root = doc.as<JsonObject>();

    // Processamento dos valores
    const char* sensor = root["sensor"];
    String hora = root["hora"];
    double temperatura = root["info"][0];
    double umidade = root["info"][1];

    // Mostra os valores
    Serial.println(sensor);
    Serial.println(hora);
    Serial.println(temperatura, 6);
    Serial.println(umidade, 6);
  }
}

void loop() {
  
}
