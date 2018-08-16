#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import time
import serial.tools.list_ports
import keyboard
from serial import Serial

def portasSeriais():
    #Lista as portas seriais
    listaPortas = serial.tools.list_ports.comports()
    conectadas = []
    for p in listaPortas:
        conectadas.append(p.device)
    return conectadas
    
def keyPressed(e):
    tecla = ', '.join(str(code) for code in keyboard._pressed_events)
    if tecla == '72': #Seta para cima
        serial.write(b'1')
    elif tecla == '80': #Seta para baixo
        serial.write(b'3')
    elif tecla == '75': #Seta para esquerda
        serial.write(b'4')
    elif tecla == '77': #Seta para direita
        serial.write(b'2')
    else:
        serial.write(b'0')

if __name__ == "__main__":
    print(u'Portas disponíveis -> ' + ', '.join(portasSeriais()))
    porta = raw_input("Digite a porta desejada: ")
    try:
        try:
            serial = Serial(porta)
            print('Conectado a porta {}'.format(porta))
            print(u'Use as setas para movimentar o veículo')
        except:
            print(u'Nao foi possível abrir a porta {}'.format(porta))
            sys.exit(1)
        keyboard.hook(keyPressed)
        keyboard.wait()
    except:
        print('Sistema encerrado!')