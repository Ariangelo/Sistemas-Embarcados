#-------------------------------------------------------------------------------
# Name:        module1
# Purpose:
#
# Author:      ari
#
# Created:     02/10/2022
# Copyright:   (c) ari 2022
# Licence:     <your licence>
#-------------------------------------------------------------------------------
import numpy as np
import speech_recognition as sr
import simpleaudio as sa

class SpeechRecognition:
    def __init__(self, ui):
        self.ui = ui
        self.recognizer = sr.Recognizer()
        self.microphone = sr.Microphone()
        self.language = 'pt_BR'

    def startMicrophone(self):
        self.playSound('VoiceActive.wav')
        with self.microphone as source:
            self.recognizer.adjust_for_ambient_noise(source)  # listen for 1 second to calibrate the energy threshold for ambient noise levels
        self.playSound('VoiceSuccess.wav')

    def playSound(self, sound):
        wave_obj = sa.WaveObject.from_wave_file('{appDir}/assets/sounds/{sound}'.format(appDir=self.ui.appPath, sound=sound))
        play_obj = wave_obj.play()
        play_obj.wait_done()

    def listen(self):
        result = ''
        self.playSound('AudioRecord.wav')
        with self.microphone as source:
            audio = self.recognizer.listen(source)
        self.playSound('AudioStop.wav')
        # received audio data and recognize it using Google Speech Recognition
        try:
            # for testing purposes, we're just using the default API key
            # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
            # instead of `r.recognize_google(audio)`
            result = self.recognizer.recognize_google(audio, language=self.language)
        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand audio")
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service; {0}".format(e))
        return result
