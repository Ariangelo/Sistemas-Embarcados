# Códigos fonte ESP8266 - Arduino IDE

Termômetro com display-OLED conectado no barramento I2C utizando ESP8266
------
![Sensor AM2320](https://cdn.instructables.com/FX4/JZ78/INT6D9T7/FX4JZ78INT6D9T7.LARGE.jpg?auto=webp&width=396)

Foi necessário a utilização da biblioteca [AM2320](../../Bibliotecas/AM2320.zip "Biblioteca sensor AM2320 para uso no ESP8266") para configuração do barramento I2C.

* [Download original da biblioteca para o sensor AM2320](https://github.com/hibikiledo/AM2320)

```c++
#include <AM2320.h>

#define SDA_PIN       4
#define SCL_PIN       5

AM2320 sensor; // Criacao da instancia do sensor

void setup() {
  Serial.begin(115200);
  sensor.begin(SDA_PIN, SCL_PIN);
 
  // outros codigos
  
}  
```
Para atualização da leitura dos valores do sensor. 
```c++
void loop() {
  String infoDisplay;
  char strDisplay[30];
  
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
  Serial.println(infoDisplay); // Imprime informacao formatada na serial
}
```
