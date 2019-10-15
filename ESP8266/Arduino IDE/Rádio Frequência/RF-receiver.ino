/*
  Exemplo utilização de recepção por Radio Frequencia RF
*/

#include <RCSwitch.h>

// Configuracoes iniciais
#define pinoLED       BUILTIN_LED
#define pinoRF        2

RCSwitch receptor = RCSwitch(); // Cria instancia de RCSwitch para recepção de informações

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  receptor.enableReceive(pinoRF); // O receptor sera conectado ao pino "pinoRF"
}

void loop() {
  if (receptor.available()) { // Verifica se existe informação disponível
    int valor = receptor.getReceivedValue(); // Armazena o valor da informação
    if (valor == 0) {
      Serial.print("Código desconhecido.");
    } else {
      Serial.print("Recebido ");
      Serial.print(valor, HEX);
      Serial.print(" / ");
      Serial.print(receptor.getReceivedBitlength()); // Obtem o valor do tamanho da informação
      Serial.print("bit ");
      Serial.print("Protoco0ol: ");
      Serial.println(receptor.getReceivedProtocol()); // Obtem o valor do protocolo de transmissão
      if (valor == 0x82B2295) { // Testa o valor da indormação recebida
        digitalWrite(BUILTIN_LED, LOW); // Liga o led
      }
      if (valor == 0x82B22A5) {
        digitalWrite(BUILTIN_LED, HIGH); // desliga o led
      }
    }
    receptor.resetAvailable(); // Prepara receptor para receber nova informação
  }
}
