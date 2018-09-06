# Códigos fonte ESP8266 - Arduino IDE

Termômetro com display-OLED conectado no barramento I2C utizando ESP8266
------

Foi necessário a utilização da biblioteca [AM2320](Documentos/https://github.com/hibikiledo/AM2320 "Biblioteca sensor AM2320 para uso no ESP8266") WiFiUDP para configuração do cliente UDP (User Datagram Protocol) necessário para conexão com o servidor NTP.

https://github.com/hibikiledo/AM2320

```c++
WiFiUDP ntpUDP; // Cliente UDP (User Datagram Protocol) para o NTP (Network Time Protocol)
```
Para atualização do relógio foi utilizado o NTP (Network Time Protocol) com sua respectiva biblioteca. 
```c++
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000); // Configuracao do Cliente NTP
```
