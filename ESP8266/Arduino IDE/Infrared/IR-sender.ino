#include <IRremoteESP8266.h>//  Biblioteca para acesso ao sensor IR - ESP8266
#include <IRsend.h>         // Biblioteca auxiliar - deve ser incluida junto com a IRremoteESP8266
#include <IRutils.h>        // Biblioteca auxiliar - deve ser incluida junto com a IRremoteESP8266

// Configuracoes iniciais
#define pinoBotao     0
#define pinoLED       BUILTIN_LED
#define pinoIR        2
// Controles basicos TV Sansung
#define POWER         0xE0E040BF // Ligar/Desligar 
#define VOL_UP        0xE0E0E01F // Vol +
#define VOL_DOWN      0xE0E0D02F // Vol -
#define CH_UP         0xE0E048B7 // Ch +
#define CH_DOWN       0xE0E008F7 // Ch -

#define SAMSUNG_BITS  32 // Tamanho do codigo de informacao para o dispositivo Sansung

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

IRsend irsend(pinoIR); //  Cria um emissor que codifica o sinal para controle de dispositivos

Botao botao;
int statusLED = HIGH;

void setup()
{
  Serial.begin(115200);
  irsend.begin(); //  Habilita o emissor para inicio de processamento dos codigos a serem enviados

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
        irsend.sendSAMSUNG(POWER, SAMSUNG_BITS); //  Codifica a informacao a ser enviada para o receptor
      }
    }
  }
  b.statusBotaoAnterior = leitura;
  return b;
}
