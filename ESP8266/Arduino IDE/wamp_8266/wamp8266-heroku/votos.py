#!/usr/bin/env python
# -*- coding: utf-8 -*-

from autobahn import wamp
from autobahn.twisted.wamp import ApplicationSession
from twisted.internet.defer import inlineCallbacks
import json

class VotosBackend(ApplicationSession):
    #Construtor usado para inicializacao 
    def __init__(self, config):
        ApplicationSession.__init__(self, config)
        self.init()
    
    #Criacao da variavel que armazenara os votos de cada robo
    def init(self):
        self._votos = {
            'bb8': 0,
            'c3po': 0,
            'r2d2': 0
        }

    @wamp.register(u'io.crossbar.demo.voto.get')
    def getVotos(self):
        #Retorna para o cliente uma json = {"robos": [{"c3po": 1}, {"r2d2": 0}, {"bb8": 1}]}
        return json.dumps({'robos': [{key: value} for key, value in self._votos.items()]})

    @wamp.register(u'io.crossbar.demo.voto.votar')
    def submitVoto(self, robo):
        #Recebe o identificador do robo e atualiza o valor na variavel
        print(u'Robo {} recebeu mais um voto'.format(robo))
        self._votos[robo] += 1
        resultado = json.dumps({robo: self._votos[robo]})
        self.publish(u'io.crossbar.demo.voto.onvoto', resultado)

    @wamp.register(u'io.crossbar.demo.voto.reset')
    def resetVotos(self):
        #Atribui 0 a todos os elementos da votacao
        self.init()
        resultado = self.getVotos()
        self.publish(u'io.crossbar.demo.voto.onreset', resultado)

    @inlineCallbacks
    def onJoin(self, details):
        #Publica todos os procedimentos para utilizacao pelos clientes
        res = yield self.register(self)
        print("Votacao - Backend: {} procedimentos registrados!".format(len(res)))

if __name__ == '__main__':
    runner = ApplicationRunner(
            url = u'ws://{}:{}/ws'.format('localhost', 8080), 
            realm = 'embarcados')
			
    runner.run(VotosBackend)
	