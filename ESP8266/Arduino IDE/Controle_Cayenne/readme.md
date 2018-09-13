# Códigos fonte ESP8266 - Arduino IDE

Termômetro com display-OLED conectado no barramento I2C utizando ESP8266 com controle utilizando Cayenne-myDevice
------

* [Como o Cayenne funciona](https://mydevices.com/cayenne/docs/intro/#introduction-how-cayenne-works)

```c++
#include <CayenneMQTTESP8266.h>
.
.
.
// Autenticacao Cayenne valores obtidos no site "Cayenne Dashboard".
char username[] = "xxxxxx-xxxx-xxxx-xxxx-xxxxxxxxx";
char password[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
char clientID[] = "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx";

void setup() {
    Cayenne.begin(username, password, clientID);
 
     // outros codigos
  
}  
```
Para atualização da leitura dos valores do sensor no sistema Cayenne. 
```c++
void loop() {
  // outros codigos
  
  Cayenne.loop();
  
  // outros codigos
}
```

Comunicação entre o dispositivo IoT e o Cayenne
```c++
//Envia informacoes para o Cayenne
CAYENNE_OUT_DEFAULT()
{
  Cayenne.virtualWrite(1, temperatura, "Temperatura", "C");
  Cayenne.virtualWrite(2, umidade, "Umidade", "%");
}

//Recebe informacoes do Cayenne
CAYENNE_IN(PIN_BOTAO1) {
  leituraBotao = !leituraBotao;
}
```

Para poder controlar o dispositivo IoT é necessário criar uma conta no Cayenne.
* [Criar uma conta no Cayenne](https://mydevices.com/cayenne/docs/getting-started/#getting-started-create-cayenne-account)

Para utilizar o ESP8266 como dispositivo IoT
* [ESP8266](https://mydevices.com/cayenne/docs/getting-started/#getting-started-esp8266)

A biblioteca Cayenne MQTT ESP possui os elementos básicos para conectar o dispositivo ESP8266 com o Cayenne usando o MQTT e a Arduino IDE. 
* Para incluir a biblioteca Cayenne

![Biblioteca Cayenne](http://deinfo.uepg.br/~ari/aulas/sistemas_embarcados/imagens/CayenneLIB.png)
