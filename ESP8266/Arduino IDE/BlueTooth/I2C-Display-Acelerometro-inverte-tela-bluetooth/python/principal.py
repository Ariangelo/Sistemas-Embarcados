import os
from delphifmx import *
from lib.uart_manager import *

class formPrincipal(Form):

    def __init__(self, owner):
        self.statusBar = None
        self.imgBluetooth = None
        self.grpBoxConfiguracaoUART = None
        self.btnDesconectarUART = None
        self.btnConectarUART = None
        self.comboPorts = None
        self.imgUART = None
        self.lblStatusBar = None
        self.grpBoxFuncao = None
        self.rbRelogio = None
        self.rbTermometro = None
        self.LoadProps(os.path.join(os.path.dirname(os.path.abspath(__file__)), "principal.pyfmx"))

        self.uart = UART(self)
        self.uart.loadPorts()
        self.selectedPort = 0
        self.connectedUART = False

    def btnConectarUARTClick(self, Sender):
        def atualizaEstado(Conectado):
            self.btnConectarUART.Enabled = not Conectado
            #self.grpBoxControles.Enabled = Conectado or self.connectedMQTT
            self.connectedUART = Conectado
            self.imgBluetooth.Visible = Conectado

        match Sender.Tag:
            case 1:
                device = self.uart.ports[self.selectedPort].device
                if self.uart.connectUART(device):
                    atualizaEstado(True)
            case 2:
                self.uart.disconnectUART()
                atualizaEstado(False)

    def comboPortsChange(self, Sender):
        self.selectedPort = Sender.ItemIndex

    def rbClick(self, Sender):
        self.uart.writeUART(Sender.Tag)
