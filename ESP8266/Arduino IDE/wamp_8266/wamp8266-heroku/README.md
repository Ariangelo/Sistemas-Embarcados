# Crossbar votação:python no Heroku

[![Deploy](https://www.herokucdn.com/deploy/button.svg)](https://heroku.com/deploy)

Este aplicativo mostra que é possível executar o roteador Crossbar utilizando o Heroku.
Pressione o botão acima para fazer upload do sistema no **Heroku**. É necessário ter uma conta no Heroku.

* Acesse o site: https://www.heroku.com/home para fazer o cadastro da conta

* Em caso de dúvidas: https://devcenter.heroku.com/articles/dyno-sleeping

Este site foi construído baseado no tutorial de [AndreMiras/crossbar-hello-python-to-heroku](https://github.com/AndreMiras/crossbar-hello-python-to-heroku).

* Para configuração do funcionamento correto do web service para ser acessado pelo ESP8266 o código JSON abaixo é necessário de ser implantado no arquivo **config.json** no diretório **.crossbar**.

```json
{
    "type": "web",
    "endpoint": {
        "type": "tcp",
        "port": "$PORT"
    },
    "paths": {
        "/": {
            "type": "static",
            "directory": "../web"
        },
        "ws": {
            "type": "websocket"
        },
        "call": {
            "type": "caller",
            "realm": "embarcados",
            "role": "anonymous",
            "options": {
                "debug": true
            }
        }
    }
}
```
