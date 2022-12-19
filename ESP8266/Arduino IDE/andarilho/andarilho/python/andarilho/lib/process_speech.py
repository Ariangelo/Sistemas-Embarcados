#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      ari
#
# Created:     01/10/2022
# Copyright:   (c) ari 2022
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import yaml
import lib.tts_manager as tts_manager

class ProcessSpeech:
    def __init__(self, ui, yamlFile):
        # Arquivo de configuração de controle do robô
        try:
            with open(yamlFile, 'rt', encoding='utf8') as file:
                self.yalmControls = yaml.safe_load(file)
            self.device = self.yalmControls['device']
            self.exitCommand = self.yalmControls['exit']
            self.speedCommand = self.yalmControls['speed']
            self.controlCommand = self.yalmControls['command']
            self.deviceActive = True
            self.tts = tts_manager.TTS(ui)
        except IOError:
            print('Impossível abrir o arquivo de configurações')
            self.deviceActive = False
                # Controle de velocidade
        self.speedControl = {'value': 30, 'min': 0, 'max': 100}


    def getCommands(self):
        return self.controlCommand

    def executeCommand(self, command, commands):
        c = set(command) & set(commands)
        return len(c) != 0

    def speakCommand(self, text):
        self.tts.speak(text);

    def sendCommand(self, newSpeed, command):
        result = {'control': 'undefined', 'value': 0, 'handling': 'undefined', 'action': 'undefined'};
        # Checks if the device identifier has been provided
        if self.executeCommand(self.device['name'], command.split()):
            print("O robô recebeu o comando: " + command)
            exit = self.executeCommand(self.exitCommand['control'], command.split())
            validCommand = False
            if not exit:
                # Process device directional commands
                for key, control in self.controlCommand.items():
                    if self.executeCommand(control['control'], command.split()):
                        result = {
                            'control': 'controle',
                            'value': control['value'],
                            'handling': key,
                            'action': 'command'
                        }
                        self.speakCommand(control['speech'])
                        validCommand = True
                # Process device speed control
                for key, speed in self.speedCommand.items():
                    if self.executeCommand(speed['control'], command.split()):
                        self.speedControl['value'] = int(newSpeed) + speed['value']
                        warning = False
                        if self.speedControl['value'] < self.speedControl['min']:
                            self.speedControl['value'] = self.speedControl['min']
                            warning = True
                        if self.speedControl['value'] > self.speedControl['max']:
                            self.speedControl['value'] = self.speedControl['max']
                            warning = True
                        if not warning:
                            self.speakCommand(speed['speech']);
                        else:
                            self.speakCommand(speed['warning']);
                        validCommand = True
                        result = {
                            'control': 'velocidade',
                            'value': self.speedControl['value'],
                            'handling': key,
                            'action': 'speed'
                        }
                if not validCommand:
                    self.speakCommand(self.device['invalid'])
            else:
                print(self.exitCommand['speech'].format(self.device['name'][0]))
                self.speakCommand(self.exitCommand['speech'])
                self.deviceActive = False
        else:
            self.speakCommand(self.device['warning'])
        return result
