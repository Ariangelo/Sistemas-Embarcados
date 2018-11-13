/*
  Exemplo utilização de transmissão por Radio Frequencia RF
*/

#include <RCSwitch.h> //  Biblioteca para acesso conexao RF - ESP8266

// Configuracoes iniciais
#define pinoBotao     0
#define pinoLED       BUILTIN_LED
#define pinoRF        2

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
Botao botao;
int statusLED = HIGH;

RCSwitch transmissor = RCSwitch(); // Cria instancia de RCSwitch para transmissão de informações

void setup() {
  Serial.begin(115200);
  botao.pino = pinoBotao;
  transmissor.enableTransmit(pinoRF); // O transmissor sera conectado ao pino "pinoRF"
  transmissor.setProtocol(6); // Será utilizado protocolo 6
}

void loop() {
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
        if (statusLED) {
          transmissor.send(0x82B2295, 28); // Envia código RF para ligar led no receptor
        } else {
          transmissor.send(0x82B22A5, 28); // Envia código RF para desligar led no receptor
        }
      }
    }
  }
  b.statusBotaoAnterior = leitura;
  return b;
}
