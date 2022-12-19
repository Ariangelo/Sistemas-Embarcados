import os
import json

from delphifmx import *

from lib.mqtt_manager import *
from lib.tts_manager import *
from lib.uart_manager import *
from lib.speech_rec import *
from lib.process_speech import *

class FormPrincipal(Form):

    def __init__(self, owner):
        self.statusBar = None
        self.lblStatusBar = None
        self.tabPrincipal = None
        self.tabControles = None
        self.grpBoxControles = None
        self.imgRobo = None
        self.btnEsqSup = None
        self.btnFrente = None
        self.btnDirSup = None
        self.btnEsquerda = None
        self.btnParar = None
        self.btnDireita = None
        self.btnDirInf = None
        self.btnVoltar = None
        self.btnEsqInf = None
        self.imgMicControle = None
        self.grpBoxVelocidade = None
        self.lblMenosVelocidade = None
        self.lblMaisVelocidade = None
        self.trackVelocidade = None
        self.grpBoxVoz = None
        self.lblMenosVolume = None
        self.lblMaisVolume = None
        self.trackVolume = None
        self.comboVoz = None
        self.imgMundoVoz = None
        self.imgVolumeVoz = None
        self.tabConfiguracoes = None
        self.lblMQTT = None
        self.lblDescMQTT = None
        self.grpBoxConfiguracaoMQTT = None
        self.edtServidor = None
        self.edtPorta = None
        self.edtCliente = None
        self.edtTopico = None
        self.btnDesconectarMQTT = None
        self.btnConectarMQTT = None
        self.lblUART = None
        self.lblDescUART = None
        self.grpBoxConfiguracaoUART = None
        self.btnDesconectarUART = None
        self.btnConectarUART = None
        self.comboPorts = None
        self.tabVoz = None
        self.panelMicrophone = None
        self.ImgMicrophone = None
        self.LblMicrophone = None
        self.imgServer = None
        self.imgPort = None
        self.imgClient = None
        self.imgTopic = None
        self.imgUART = None
        self.imgBluetooth = None
        self.imgWiFi = None
        self.imgMic = None

        self.appPath = os.path.dirname(os.path.abspath(__file__))
        self.LoadProps('{}\mainApp.pyfmx'.format(self.appPath))

        self.mqtt = MQTT(self)
        self.connectedMQTT = False

        self.uart = UART(self)
        self.uart.loadPorts()
        self.selectedPort = 0
        self.connectedUART = False

        self.tts = TTS(self)
        self.tts.loadVoices()

        self.sr = SpeechRecognition(self)

        self.processSpeech = ProcessSpeech(self, '{}/assets/files/controls.yaml'.format(self.appPath))
        self.voiceCommands = list(self.processSpeech.getCommands().keys())

        self.currentActionValue = 3;
        self.currentSpeedValue = 20.0

    def publishMessage(self, control, action = 3, speed = 20.0, speech = ''):
        message = {'control': control, 'action': action, 'speed': speed, 'speech': speech}
        if self.connectedUART:
            self.uart.writeUART(json.dumps(message))
        if self.connectedMQTT:
            self.mqtt.clienteMQTT.publish(self.mqtt.topico, json.dumps(message))

    def setAction(self, handler, manual=True):
        control = handler['control']
        if control != 'undefined':
            speech = self.processSpeech.yalmControls[handler['action']][handler['handling']]['speech']
            if control == 'velocidade':
                self.currentSpeedValue = handler['value']
            else:
                self.currentActionValue = handler['value']
            self.publishMessage(control, action=self.currentActionValue, speed=self.currentSpeedValue, speech=speech)
            if manual:
                self.processSpeech.speakCommand(speech)

    def FormFocusChanged(self, Sender):
        #makes the cursor trick
        if not Application.MainForm.Active:
            Application.MainForm.Activate()

    def btnClick(self, Sender):
        self.sr.playSound('EffectTick.wav')
        self.setAction({
            'control': 'controle',
            'value': Sender.Tag,
            'handling': self.voiceCommands[Sender.Tag - 1],
            'action': 'command'
        })

    def trackVelocidadeChange(self, Sender):
        value = round(Sender.Value, 1)
        speedHandler = 'quick' if value > self.currentSpeedValue else 'slow';
        self.setAction({
            'control': 'velocidade',
            'value': value,
            'handling': speedHandler,
            'action': 'speed'
        })

    def trackVolumeChange(self, Sender):
        self.tts.setVolume(Sender.Value)

    def comboVozChange(self, Sender):
        self.tts.setVoice(Sender.ItemIndex)

    def tabConfiguracoesClick(self, Sender):
        pass

    def edtKeyUp(self, Sender, Key, KeyChar, Shift):
        pass

    def btnConectarMQTTClick(self, Sender):
        def atualizaEstado(Conectado):
            self.btnConectarMQTT.Enabled = not Conectado
            self.grpBoxControles.Enabled = Conectado or self.connectedUART
            self.grpBoxVelocidade.Enabled = self.grpBoxControles.Enabled
            self.connectedMQTT = Conectado
            self.imgWiFi.Enabled = Conectado

        match Sender.Tag:
            case 1:
                if self.mqtt.conectaMQTT():
                    self.tabPrincipal.ActiveTab = self.tabControles
                    atualizaEstado(True)
                    self.mqtt.clienteMQTT.loop()
                #else:
                #    self.lblStatusBar.Text = 'Não foi possível conectar ao Broker.'
            case 2:
                self.mqtt.clienteMQTT.disconnect()
                self.tabPrincipal.ActiveTab = self.tabConfiguracoes
                atualizaEstado(False)
            case other:
                print('No match found')

    def btnConectarUARTClick(self, Sender):
        def atualizaEstado(Conectado):
            self.btnConectarUART.Enabled = not Conectado
            self.grpBoxControles.Enabled = Conectado or self.connectedMQTT
            self.grpBoxVelocidade.Enabled = self.grpBoxControles.Enabled
            self.connectedUART = Conectado

        match Sender.Tag:
            case 1:
                device = self.uart.ports[self.selectedPort].device
                if self.uart.connectUART(device):
                    self.tabPrincipal.ActiveTab = self.tabControles
                    atualizaEstado(True)
                #else:
                #    self.lblStatusBar.Text = 'Não foi possível conectar à porta {}'.format(device)
            case 2:
                self.uart.disconnectUART()
                self.tabPrincipal.ActiveTab = self.tabConfiguracoes
                atualizaEstado(False)

    def comboPortsChange(self, Sender):
        self.selectedPort = Sender.ItemIndex

    def imgMicrophoneClick(self, Sender):
        self.sr.startMicrophone()
        #self.processSpeech.speakCommand(self.processSpeech.yalmControls['device']['init'])
        self.imgMicControle.Visible = True
        self.tabPrincipal.ActiveTab = self.tabControles

    def imgMicControleClick(self, Sender):
        self.setAction(self.processSpeech.sendCommand(self.currentSpeedValue, self.sr.listen().lower()), manual=False)
