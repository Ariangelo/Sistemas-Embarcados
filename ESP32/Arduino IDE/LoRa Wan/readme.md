# Códigos fonte ESP8266 - Arduino IDE

Infravermelho utizando ESP8266
------

![ESP32-LoRa](../../../Imagens/ESP32-LoRa.png)

* A especificação **LoRaWAN** é um protocolo de rede LPWA (Low Power, Wide Area) projetado para conectar sem fio sistemas operados por bateria à Internet em ao outros tipos de redes, e tem como alvo os principais requisitos da Internet das Coisas (IoT).

* Instalação da biblioteca **LoRaWAN**

![Instalação IRremoteESP8266](../../../Imagens/LoRa.png)

* Detalhes e particularidades do código usando a IDE Arduino e ESP8266 como receptor de códigos infravermelho

```c++

#include <IRremoteESP8266.h>//  Biblioteca para acesso ao sensor IR - ESP8266
#include <IRrecv.h>         // Biblioteca auxiliar - deve ser incluida junto com a IRremoteESP8266
#include <IRutils.h>        // Biblioteca auxiliar - deve ser incluida junto com a IRremoteESP8266

// Configuracoes iniciais
#define pinoIR    2

IRrecv receptor(pinoIR);   //  Cria um receptor que decodifica o sinal do sensor IR - codigos do controle remoto
decode_results resultados; //  Variavel que aramzenara os resultados recebidos

void setup() {
  Serial.begin(115200);
  receptor.enableIRIn();  //  Habilita o receptor para inicio de processamento dos codigos recebidos do emissor IR
}

void loop() {
  if (receptor.decode(&resultados)) {   //  Decodifica o codigo da informacao enviada pelo emissor IR
    serialPrintUint64(resultados.value, HEX); //  Mostra o valor em HEX do resultado recebido
    Serial.println("");
    receptor.resume();  //  Continua a aguardar o envio de informacoes peso emissor IR
  }
}

```
