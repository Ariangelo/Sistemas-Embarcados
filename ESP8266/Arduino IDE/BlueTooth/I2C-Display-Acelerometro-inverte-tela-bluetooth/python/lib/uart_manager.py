import os
import serial.tools.list_ports
from serial import Serial

class UART():
    def __init__(self, ui):
        self.ui = ui
        self.uart = None
        self.port = ''
        self.ports = []

    def loadPorts(self):
        #'description', 'device'
        for p in serial.tools.list_ports.comports():
            self.ports.append(p)
            self.ui.comboPorts.Items.Add(p.description)

    def connectUART(self, port):
        try:
            self.uart = Serial(port)
            self.ui.lblStatusBar.Text = 'Conectado a porta {}'.format(port)
            self.port = port
            return True
        except:
            self.ui.lblStatusBar.Text = 'Nao foi possível conectar a porta {}'.format(port)
            return False

    def disconnectUART(self):
        try:
            self.ui.lblStatusBar.Text = 'Desconectado da porta {}'.format(self.port)
            self.uart.close()
        except:
            self.ui.lblStatusBar.Text = ''

    def writeUART(self, value):
        self.uart.write(u'{}\r\n'.format(value).encode())



