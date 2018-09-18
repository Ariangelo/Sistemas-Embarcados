# Códigos fonte ESP8266 - Arduino IDE

Configuração e utilização de multiplexador 4051 com ESP8266
------
![Multiplexador 4051](http://deinfo.uepg.br/~ari/aulas/sistemas_embarcados/imagens/4051.png) ![Multiplexador 4051 - Esquema](http://deinfo.uepg.br/~ari/aulas/sistemas_embarcados/imagens/4051(esquema).png)

* Procedimento criado para selecionar o canal do multiplexador

```c++
//Controle dos canais do multiplexador
int pins[3] = {PIN_S0, PIN_S1, PIN_S2};
void muxWrite(int canal) {
  for (int i = 0; i < 3; i++)  {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], bitRead(canal, i));
  }
}
```

* Comunicação com o canal virtual do Cayenne

```c++
//Criado um canal virtual 21
//O canal 21 representa o canal 1 do multiplexador
//É chamado o procedimento muxWrite com parâmetro 1 para o parâmetro canal
CAYENNE_IN(21) {
  Serial.println("Mux canal 1");
  muxWrite(1);
}

```
* Criação do canal virtual no Cayenne

![Criação do canal virtual no Cayenne](http://deinfo.uepg.br/~ari/aulas/sistemas_embarcados/imagens/Cayenne-criar-canal.png)
