# Códigos fonte ESP8266 - Arduino IDE

Protocolo de comunicação WAMP - Crossbar.io utizando ESP8266
------
* O protocolo WAMP é um esforço da comunidade e a especificação é disponibilizada gratuitamente sob uma licença aberta. O projeto original e a proposta foram criados pelos desenvolvedores da **Crossbar.io** em 2012 e o desenvolvimento da **WAMP** (Web Application Messaging Protocol) é mantido pela Crossbar.io.
* [Informações no site original do WAMP](https://wamp-proto.org/)

* O **Crossbar.io** é uma plataforma de rede de código aberto para aplicativos distribuídos como microsserviços. É responsável pela implementação do Protocolo Aberto de Mensagens de Aplicativos da Web **WAMP**, possui recursos avançados de comunicação, é escalável, robusto e seguro.
* [Informações no site original do Crossbar.io](https://crossbar.io/)

* Detalhes e particularidades do código usando a IDE Arduino e ESP8266

```c++

const char* host = "app-votar.herokuapp.com"; // Servidor - Roteador dos procedimentos publicados
const int httpPort = 80; // Porta do servidor
const String url = "/call"; // Caminho do webservice dos procedimentos publicados

```

* Chama do microsserviço utilizando **web service**

```c++

 String data = "{\"procedure\": \"io.crossbar.demo.voto.votar\", \"args\": [ \"r2d2\"]}"; // Votar no R2D2
 // Requisicao postada no servidor
 client.print("POST " + url + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Content-Type: application/json" + "\r\n" +
              "Content-Length: " + data.length() + "\r\n\r\n" +
              data);

```

* [Exemplo de Servidor-Roteador utilizando a tecnologia WAMP/Crossbar](wamp8266-heroku "Procedimentos para upload do servidor WAMP/Crossbar")
