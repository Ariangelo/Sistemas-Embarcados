# Códigos fonte ESP8266 - Arduino IDE

Termômetro com display-OLED conectado no barramento I2C utizando ESP8266
------

Foi necessário a utilização da biblioteca [AM2320](ESP8266/Bibliotecas/AM2320.zip "Biblioteca sensor AM2320 para uso no ESP8266") para configuração do barramento I2C.
```c++
#include <AM2320.h>

#define SDA_PIN       4
#define SCL_PIN       5
#define ENDERECO_OLED 0x3C
#define TAMANHO       GEOMETRY_128_32

AM2320 sensor; // Criacao da instancia do sensor

void setup() {
  sensor.begin(SDA_PIN, SCL_PIN);
 
  // outros codigos
  
}  
```
Para atualização da leitura dos valores do sensor. 
```c++
void loop() {
    if (sensor.measure()) {
      temperatura = sensor.getTemperature();
      umidade = sensor.getHumidity();
      sprintf(strDisplay, "%.1fºC  -  %.0f%%", temperatura, umidade);
    } else {
      int erroSensor = sensor.getErrorCode();
      switch (erroSensor) {
        case 1:
          infoDisplay = "Sensor não conectado";
          break;
        case 2:
          infoDisplay = "Dados do sensor inválido";
          break;
      }
    }
}
```
