#-------------------------------------------------------------------------------
# Name:        tts_manager
# Purpose:
#
# Author:      ari
#
# Created:     02/09/2022
# Copyright:   (c) ari 2022
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import pyttsx3

class TTS:
    def __init__(self, ui):
        # Configuracao da tradução do comando
        self.ui = ui
        self.tts = pyttsx3.init()
        self.tts.setProperty('rate', 180)
        self.setVolume(ui.trackVolume.Value)

    def loadVoices(self):
        for v in self.getVoices():
            voice = v.name.replace('Microsoft ', '')
            voice = voice.replace('Desktop ', '')
            self.ui.comboVoz.Items.Add(voice)

    def getVoices(self):
        return self.tts.getProperty('voices')  #getting details of current voice

    def setVoice(self, voice):
        self.tts.setProperty('voice', self.getVoices()[voice].id) #changing index, changes voices.

    def setVolume(self, volume):
        self.tts.setProperty('volume',volume  / 100)  # setting up volume level  between 0 and 1

    def speak(self, text):
        self.tts.say(text)
        self.tts.runAndWait()
        self.tts.stop()
