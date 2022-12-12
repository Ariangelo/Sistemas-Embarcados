import 'dart:async';
import 'dart:math';

import 'package:andarilho/generated/l10n.dart';
import 'package:andarilho/screens/main_page/main_page.dart';
import 'package:andarilho/utility/process_speech_command.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:speech_to_text/speech_recognition_result.dart';
import 'package:speech_to_text/speech_to_text.dart';

import 'bluetooth_configuration_page.dart';
import 'mqtt_configuration_page.dart';

class SpeechRecognitionPage extends StatefulWidget {
  final MainPage mainPage;
  SpeechRecognitionPage({Key? key, required this.mainPage}) : super(key: key);

  final SpeechRecognitionPageState speechRecognitionPageState = SpeechRecognitionPageState();

  get speech => speechRecognitionPageState.speech;
  get level => speechRecognitionPageState.level;

  void setEnvironmentState() {
    speechRecognitionPageState.setEnvironmentState();
  }

  void setStateVolume(value) {
    speechRecognitionPageState.setStateVolume(value);
  }

  void startListening(value) {
    speechRecognitionPageState.startListening(value);
  }

  @override
  SpeechRecognitionPageState createState() => speechRecognitionPageState;
}

class SpeechRecognitionPageState extends State<SpeechRecognitionPage> {
  late MQTTConfigurationPage mqttConfigurationPage = widget.mainPage.mqttConfigurationPage;
  late BluetoothConfigurationPage bluetoothConfigurationPage = widget.mainPage.bluetoothConfigurationPage;

  late bool connectedMQTT;
  late bool connectedBluetooth;
  late BluetoothConnection bluetoothConnection;

  late SpeechToText speech;
  late bool hasSpeech;
  bool isInitialize = false;
  bool isListening = false;
  String lastWords = '';
  String lastError = '';
  String lastStatus = '';
  String currentLocaleId = '';
  List<LocaleName> localeNames = [];

  ProcessSpeechCommand processSpeechCommand = ProcessSpeechCommand();

  double level = 0.0;
  double minSoundLevel = 50000;
  double maxSoundLevel = -50000;

  @override
  void initState() {
    super.initState();
    setEnvironmentState();
    speech = SpeechToText();
    hasSpeech = false;
  }

  void setEnvironmentState() {
    setState(() {
      connectedMQTT = mqttConfigurationPage.connectedMQTT;
      connectedBluetooth = bluetoothConfigurationPage.deviceConnected['connected'];
      if (bluetoothConfigurationPage.bluetoothConnection != null) {
        bluetoothConnection = bluetoothConfigurationPage.bluetoothConnection;
      }
    });
  }

  void initSpeechState(SpeechToText speech) {
    speech.initialize().then((value) => setState(() => hasSpeech = value)).whenComplete(() {
      if (hasSpeech) {
        speech.locales().then((value) => setState(() => localeNames = value));
        speech.systemLocale().then((value) => setState(() => currentLocaleId = value?.localeId ?? ''));
        processSpeechCommand.speakCommand(processSpeechCommand.yalmControls['device']['init']);
        widget.mainPage.controlPage.hasSpeechChange(hasSpeech);
      }
    }).onError((error, stackTrace) => setState(() {
          print(error.toString());
          lastError = '${S().voice_recognition_failed}: ${error.toString()}';
          hasSpeech = false;
          widget.mainPage.controlPage.hasSpeechChange(hasSpeech);
        }));
  }

  void cancelSpeechState(SpeechToText speech) {
    speech.cancel().whenComplete(() {
      processSpeechCommand.textToSpeechManager.tts.stop();
      setState(() => hasSpeech = false);
      widget.mainPage.controlPage.hasSpeechChange(hasSpeech);
    });
  }

  void resultListener(SpeechRecognitionResult result) {
    setState(() {
      lastWords = result.recognizedWords;
      level = 0.0;
    });
    widget.mainPage.controlPage.setAction(
        processSpeechCommand.sendCommand(widget.mainPage.controlPage.currentSpeedValue, lastWords.toLowerCase()));
  }

  void soundLevelListener(double level) {
    minSoundLevel = min(minSoundLevel, level);
    maxSoundLevel = max(maxSoundLevel, level);
    setState(() => this.level = level);
    widget.mainPage.controlPage.setEnvironmentState();
  }

  void startListening(SpeechToText speech) {
    speech.listen(
        onResult: resultListener,
        partialResults: false,
        localeId: currentLocaleId,
        onSoundLevelChange: soundLevelListener,
        cancelOnError: true,
        listenMode: ListenMode.dictation);
    setState(() => lastWords = '');
  }

  void setStateVolume(value) {
    setState(() => widget.mainPage.controlPage.volume);
  }

  void onChangedVolume(value) {
    setStateVolume(value);
    widget.mainPage.controlPage.onChangedVolume(value);
  }

  @override
  Widget build(BuildContext context) {
    return Column(children: [
      Row(mainAxisAlignment: MainAxisAlignment.spaceBetween, children: [
        const Expanded(child: Divider(indent: 10)),
        OutlinedButton(
            style: ButtonStyle(
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(30.0),
            ))),
            onPressed: () {},
            child: Row(children: [
              Text(
                '${S().voice_title}   ',
              ),
              Icon(connectedMQTT ? Icons.sensors : Icons.sensors_off),
              Icon(connectedBluetooth ? Icons.bluetooth : Icons.bluetooth_disabled)
            ])),
        const Expanded(child: Divider(endIndent: 10)),
      ]),
      hasSpeech ? hasSpeechInfo() : notSpeechInfo(),
    ]);
  }

  Widget hasSpeechInfo() {
    return Column(children: [
      Container(
          margin: const EdgeInsets.all(10),
          padding: const EdgeInsets.all(20),
          decoration: BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
          child: Column(children: [
            Row(
                mainAxisAlignment: MainAxisAlignment.spaceBetween,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  const Icon(Icons.language, size: 30),
                  SizedBox(
                      width: 300,
                      child: DropdownButton<String>(
                        onChanged: hasSpeech ? (selectedVal) => setState(() => currentLocaleId = selectedVal!) : null,
                        value: currentLocaleId,
                        underline: Container(
                          height: 0,
                        ),
                        items: localeNames
                            .map(
                              (localeName) => DropdownMenuItem(
                                value: localeName.localeId,
                                child: Text(localeName.name),
                              ),
                            )
                            .toList(),
                      )),
                ]),
            Container(
                padding: const EdgeInsets.symmetric(vertical: 20),
                child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      speech.isListening
                          ? const Icon(Icons.hearing, size: 30)
                          : const Icon(Icons.hearing_disabled, size: 30),
                      SizedBox(
                          width: 300,
                          child: Text(speech.isListening ? S().voice_receiving_message : S().voice_waiting_message,
                              style: Theme.of(context).textTheme.subtitle1))
                    ])),
            Container(
                padding: const EdgeInsets.only(top: 5),
                child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      Icon(lastWords == '' ? Icons.textsms_outlined : Icons.textsms, size: 30),
                      SizedBox(width: 300, child: Text(lastWords, style: Theme.of(context).textTheme.subtitle1))
                    ])),
            Container(
                padding: const EdgeInsets.only(top: 5),
                child: Row(
                    mainAxisAlignment: MainAxisAlignment.spaceBetween,
                    crossAxisAlignment: CrossAxisAlignment.center,
                    children: [
                      const Icon(Icons.volume_up, size: 30),
                      Expanded(
                          child: Slider(
                        value: widget.mainPage.controlPage.volume,
                        min: 0,
                        max: 1.0,
                        divisions: 10,
                        label: widget.mainPage.controlPage.volume.toString(),
                        onChanged: (value) => onChangedVolume(value),
                        onChangeEnd: (value) => {}, //setSpeed(value.round().toString()),
                      ))
                    ]))
          ])),
      Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Text(S().voice_start_message),
          const Divider(height: 50, indent: 100, endIndent: 100),
          microphoneButton(false),
          const Divider(height: 50, indent: 100, endIndent: 100),
          ElevatedButton(
            onPressed: () => cancelSpeechState(speech),
            child: Text(S().voice_exit_message),
          )
        ],
      )
    ]);
  }

  Widget notSpeechInfo() {
    return Expanded(
        child: Column(
      mainAxisAlignment: MainAxisAlignment.center,
      children: [
        Text(S().voice_start_message),
        const Divider(height: 50, indent: 100, endIndent: 100),
        microphoneButton(true)
      ],
    ));
  }

  Widget microphoneButton(initialize) {
    return Container(
      width: 160,
      height: 160,
      alignment: Alignment.center,
      decoration: BoxDecoration(
        boxShadow: [BoxShadow(blurRadius: .26, spreadRadius: level * 2.5, color: Colors.black.withOpacity(.05))],
        color: Colors.white,
        borderRadius: const BorderRadius.all(Radius.circular(200)),
      ),
      child: IconButton(
          iconSize: 80,
          icon: const Icon(Icons.mic),
          onPressed: connectedMQTT || connectedBluetooth
              ? initialize
                  ? () => initSpeechState(speech)
                  : () => startListening(speech)
              : () => ScaffoldMessenger.of(context).showSnackBar(SnackBar(
                    content: Text(S().warning_conection_message),
                  ))),
    );
  }
}
