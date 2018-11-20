# Crossbar hello:python no Heroku

[![Deploy](https://www.herokucdn.com/deploy/button.svg)](https://heroku.com/deploy)

Este aplicativo de demonstração mostra que é possível executar o roteador Crossbar utilizando o Heroku.

Veja http://crossbar.io/docs/Setup-on-Heroku/ para mais detalhes.
Lembre-se que os aplicativos gratuitos só podem estar ativos 18 horas por dia.

Saiba mais: https://devcenter.heroku.com/articles/dyno-sleeping

Este site foi construído baseado no [AndreMiras/crossbar-hello-python-to-heroku](https://github.com/AndreMiras/crossbar-hello-python-to-heroku).

```
heroku ps:scale web=0
heroku logs --tail
```
