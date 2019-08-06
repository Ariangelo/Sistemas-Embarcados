/*
  Debounce

  Cada vez que o pino de entrada passa de BAIXO para ALTO (push buttom por exemplo)
  o pino de saída é alternado de BAIXO para ALTO ou vice e versa.
  Cria-se um atraso na resposta do push buttom para eliminação ruído.
  O circuito:
   - LED conectado do pino 2 ao terra
   - botão ligado do pino 0 a + 3.3V
   - resistor de 10k interligando do pino 0 ao terra
  Originalmente criado por
   - David A. Mellis (2006)
   - Limor Fried (2011)
   - Mike Walters (2012)
   - Arturo Guadalupi (2016)

  Este exemplo é de domínio público.
  http://www.arduino.cc/en/Tutorial/Debounce
*/

// Configuracoes iniciais
#define pinoBotao 0
#define pinoLED   2

// Variveis de controle
int statusLED = HIGH;
int statusBotao;
int statusAnteriorBotao = LOW;

unsigned long tempoAnteriorDebounce = 0;
unsigned long debounceDelay = 50;   // tempo do debounce time; aumentar se saida oscila

void setup() {
  pinMode(pinoBotao, INPUT);
  pinMode(pinoLED, OUTPUT);

  digitalWrite(pinoLED, statusLED);
}

void loop() {
  int reading = digitalRead(pinoBotao);
  // verifica o botao foi pressionado (entrada mudou de LOW para HIGH)
  // e se foi tempo suficiente para ignorar qualquer ruído:
  // VErifica a mudanca de status por ruído ou presionar o botao:
  if (reading != statusAnteriorBotao) {
    // reset
    tempoAnteriorDebounce = millis();
  }

  if ((millis() - tempoAnteriorDebounce) > debounceDelay) {
    // seja qual for a leitura, verifica se esta ocorreu a mais tempo que o debounce
    // se isto ocorrer então passa a ser o estado atual:
    // verifica se o estado do botão foi alterado:
    if (reading != statusBotao) {
      statusBotao = reading;
      // somente inverte o LED se o novo estado fo botao for HIGH
      if (statusBotao == HIGH) {
        statusLED = !statusLED;
      }
    }
  }
  digitalWrite(pinoLED, statusLED);
  // armazena a leitura e na próxima passagem pelo loop sera o statusAnteriorBotao:
  statusAnteriorBotao = reading;
}
