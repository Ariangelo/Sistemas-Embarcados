#-------------------------------------------------------------------------------
# Name:        mqtt_manager
# Purpose:
#
# Author:      ari
#
# Created:     02/09/2022
# Copyright:   (c) ari 2022
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import paho.mqtt.client as mqtt

class MQTT():
    def __init__(self, ui):
        # Configuracao da comunicacao MQTT
        self.ui = ui
        self.clienteMQTT = mqtt.Client(ui.edtCliente.Text)
        self.servidorMQTT = ui.edtServidor.Text
        self.porta = int(ui.edtPorta.Text)
        self.topico = ui.edtTopico.Text

    def onConnect(self, cliente, userdata, flags, rc):
        self.ui.lblStatusBar.Text = 'Conectado ao Broker - {}'.format(self.servidorMQTT)

    def onDisconnect(self, cliente, userdata, rc):
        self.ui.lblStatusBar.Text = 'Desconectado do Broker - {}'.format(self.servidorMQTT)

    def conectaMQTT(self):
        self.clienteMQTT.on_connect = self.onConnect
        self.clienteMQTT.on_disconnect = self.onDisconnect
        try:
            self.clienteMQTT.connect(self.servidorMQTT, self.porta)
            self.clienteMQTT.loop()
            return True
        except:
            return False










