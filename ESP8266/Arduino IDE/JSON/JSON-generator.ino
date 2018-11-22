// ArduinoJson - arduinojson.org
// Exemplo de como gerar uma JSON com ArduinoJson.

#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial.println();

  // Alocacao de espaco para o documento JSON
  // 200 é o tamanho em bytes que será alocado na memoria
  // Use arduinojson.org/assistant para computar a capacidade
  StaticJsonDocument<200> doc;

  // Transforma o documento (doc) em um objeto JSON (root)
  JsonObject root = doc.to<JsonObject>();

  // Adicionando valores na JSON
  root["sensor"] = "AM2320";
  root["hora"] = "23:58:58";

  // Adicionando arrays na JSON
  JsonArray data = root.createNestedArray("info");
  data.add(28.6);
  data.add(82.2);

  // Serializa o objeto e mostra na Serial
  serializeJson(root, Serial);
  // Sera impresso: {"sensor":"AM2320","hora":"23:58:58","info":[28.6, 82.2]}
  Serial.println();
  // Ou entao de forma formatada
  serializeJsonPretty(root, Serial);
  Serial.println();
  // Sera impresso:
  // {
  //   "sensor": "AM2320",
  //   "hora":"23:58:58",
  //   "info": [
  //     28.6,
  //     82.2
  //   ]
  // }

  // Tambem e possivel serializar para uma String ou char info[]
  String resultado;
  serializeJson(root, resultado);
  char info[200];
  serializeJsonPretty(root, info);
  Serial.println(resultado);
  Serial.println(info);
}

void loop() {
  // not used in this example
}

// Visit https://arduinojson.org/v6/example/generator/ for more.
