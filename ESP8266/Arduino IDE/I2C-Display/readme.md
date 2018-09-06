# Códigos fonte ESP8266 - Arduino IDE

Relógio com display-OLED conectado no barramento I2C utizando ESP8266
------

* [Documentação para o uso do display OLED SSD1306 com o ESP 8266](https://github.com/ThingPulse/esp8266-oled-ssd1306)

Foi necessário a utilização da biblioteca WiFiUDP para configuração do cliente UDP (User Datagram Protocol) necessário para conexão com o servidor NTP.
```c++
WiFiUDP ntpUDP; // Cliente UDP (User Datagram Protocol) para o NTP (Network Time Protocol)
```
Para atualização do relógio foi utilizado o NTP (Network Time Protocol) com sua respectiva biblioteca. 
```c++
NTPClient horaCliente(ntpUDP, "pool.ntp.org", TIME_ZONE * 3600, 60000); // Configuracao do Cliente NTP
```

