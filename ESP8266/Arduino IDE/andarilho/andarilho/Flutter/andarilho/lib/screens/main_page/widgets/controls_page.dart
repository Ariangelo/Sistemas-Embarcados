import 'dart:convert';
import 'dart:math';

import 'package:andarilho/generated/l10n.dart';
import 'package:andarilho/screens/main_page/main_page.dart';
import 'package:andarilho/screens/main_page/widgets/digital_ink_page.dart';
import 'package:andarilho/utility/process_speech_command.dart';
import 'package:andarilho/utility/text_to_%20speech_manager.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class ControlsPage extends StatefulWidget {
  final MainPage mainPage;
  ControlsPage({Key? key, required this.mainPage}) : super(key: key);

  final ControlsPageState controlsPageState = ControlsPageState();

  get volume => controlsPageState.volume;
  get currentSpeedValue => controlsPageState.currentSpeedValue;

  void setEnvironmentState() {
    controlsPageState.setEnvironmentState();
  }

  void onChangedVolume(value) {
    controlsPageState.onChangedVolume(value);
  }

  void setAction(Map<String, dynamic> value) {
    controlsPageState.setAction(value);
  }

  void hasSpeechChange(bool value) {
    controlsPageState.hasSpeechChange(value);
  }

  @override
  ControlsPageState createState() => controlsPageState;
}

class ControlsPageState extends State<ControlsPage> {
  static const double INIT_SPPED = 20.0;
  bool showControls = true;

  late bool connectedMQTT;
  late bool connectedBluetooth;
  late BluetoothConnection bluetoothConnection;

  late double sliderSpeedValue;
  late double currentSpeedValue;
  late int currentActionValue;
  String speedHandler = 'quick';

  double level = 0.0;
  double volume = 0.5; // Range: 0-1
  bool hasSpeech = false;
  TextToSpeechManager textToSpeechManager = TextToSpeechManager();
  ProcessSpeechCommand processSpeechCommand = ProcessSpeechCommand();
  String? currentLocaleId;
  List<String> localeNames = <String>[];

  @override
  void initState() {
    super.initState();
    textToSpeechManager.updateLocales().whenComplete(() {
      localeNames = textToSpeechManager.localeNames;
      currentLocaleId = textToSpeechManager.currentLocaleId;
    });
    setEnvironmentState();
    sliderSpeedValue = INIT_SPPED;
    currentSpeedValue = INIT_SPPED;
    currentActionValue = 3;
  }

  @override
  void dispose() {
    super.dispose();
  }

  void setEnvironmentState() {
    setState(() {
      level = widget.mainPage.speechRecognitionPage.level;
      connectedMQTT = widget.mainPage.mqttConfigurationPage.connectedMQTT;
      connectedBluetooth = widget.mainPage.bluetoothConfigurationPage.deviceConnected['connected'];
      if (widget.mainPage.bluetoothConfigurationPage.bluetoothConnection != null) {
        bluetoothConnection = widget.mainPage.bluetoothConfigurationPage.bluetoothConnection;
      }
    });
  }

  void publishMessage({required control, action = 3, speed = INIT_SPPED, speech = ''}) {
    String message = '{"control": "$control", "action": $action, "speed": $speed, "speech": "$speech"}';
    if (connectedBluetooth) {
      bluetoothConnection.output.allSent
          .whenComplete(() => bluetoothConnection.output.add(Uint8List.fromList(utf8.encode('$message\r\n'))));
    }
    if (connectedMQTT) {
      setState(() => widget.mainPage.mqttConfigurationPage.mqttClientManager.publishMessage(
          widget.mainPage.mqttConfigurationPage.mqttClientManager.topic, utf8.encode(message)));
    }
  }

  void setAction(Map<String, dynamic> handler) {
    String control = handler['control'];
    String speech = processSpeechCommand.yalmControls[handler['action']][handler['handling']]['speech'];
    setState(() => control == 'velocidade'
        ? currentSpeedValue = handler['value'].toDouble()
        : currentActionValue = handler['value']);
    publishMessage(control: control, action: currentActionValue, speed: currentSpeedValue.round(), speech: speech);
    processSpeechCommand.speakCommand(speech);
  }

  void onChangedVolume(value) {
    setState(() => volume = value);
    widget.mainPage.speechRecognitionPage.setStateVolume(value);
    textToSpeechManager.tts.setVolume(volume);
  }

  void hasSpeechChange(bool value) {
    setState(() => hasSpeech = value);
  }

  @override
  Widget build(BuildContext context) {
    List<dynamic> handling = [
      [90, 6, 'northwest'],
      [135, 1, 'north'],
      [180, 7, 'northeast'],
      [45, 2, 'west'],
      [-1, 3, 'stop'],
      [225, 4, 'east'],
      [0, 8, 'southwest'],
      [315, 5, 'south'],
      [270, 9, 'southeast']
    ];
    return Column(children: <Widget>[
      Row(mainAxisAlignment: MainAxisAlignment.spaceBetween, children: [
        const Expanded(child: Divider(indent: 10)),
        OutlinedButton(
            style: ButtonStyle(
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(RoundedRectangleBorder(
              borderRadius: BorderRadius.circular(30.0),
            ))),
            onPressed: () {},
            onLongPress: () => connectedMQTT || connectedBluetooth ? setState(() => showControls = !showControls) : null,
            child: Row(children: [
              Text(
                '${S().controls_title}   ',
              ),
              Icon(connectedMQTT ? Icons.sensors : Icons.sensors_off),
              Icon(connectedBluetooth ? Icons.bluetooth : Icons.bluetooth_disabled)
            ])),
        const Expanded(child: Divider(endIndent: 10)),
      ]),
      showControls
          ? Expanded(
              child: Container(
                  margin: const EdgeInsets.symmetric(vertical: 5, horizontal: 10),
                  padding: const EdgeInsets.all(5),
                  decoration:
                      BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
                  child: Stack(
                    children: [
                      Center(
                          child: Image.asset(
                        'assets/images/Robo detector.png',
                        fit: BoxFit.fitWidth,
                      )),
                      Visibility(
                          visible: connectedMQTT || connectedBluetooth,
                          child: Center(
                              child: Container(
                                  //padding: const EdgeInsets.symmetric(vertical: 100, horizontal: 60),
                                  padding: const EdgeInsets.all(60),
                                  child: GridView.count(
                                    // Create a grid with 3 columns. If you change the scrollDirection to
                                    // horizontal, this produces 3 rows.
                                    crossAxisCount: 3,
                                    // Generate 9 widgets that display their index in the List.
                                    children: List.generate(9, (index) {
                                      IconData iconAction =
                                          index == 4 ? Icons.cancel_outlined : Icons.transit_enterexit;
                                      return Container(
                                          padding: const EdgeInsets.all(15),
                                          child: FloatingActionButton(
                                              elevation: 10,
                                              onPressed: () {
                                                setState(() => currentActionValue = handling[index][1]);
                                                setAction({
                                                  'control': 'controle',
                                                  'value': handling[index][1],
                                                  'handling': handling[index][2],
                                                  'action': 'command'
                                                });
                                              },
                                              child: Transform.rotate(
                                                angle: handling[index][0] * pi / 180,
                                                child: Icon(iconAction, size: 30),
                                              )));
                                    }),
                                  )))),
                      Visibility(
                          visible: hasSpeech && (connectedMQTT || connectedBluetooth),
                          child: Align(
                              alignment: Alignment.bottomRight,
                              child: Container(
                                  width: 60,
                                  height: 60,
                                  alignment: Alignment.center,
                                  decoration: BoxDecoration(
                                    boxShadow: [
                                      BoxShadow(
                                          blurRadius: .26,
                                          spreadRadius: level * 1.5,
                                          color: Colors.black.withOpacity(.05))
                                    ],
                                    color: Colors.white,
                                    borderRadius: const BorderRadius.all(Radius.circular(60)),
                                  ),
                                  child: FloatingActionButton(
                                    //elevation: 10,
                                    onPressed: () => widget.mainPage.speechRecognitionPage
                                        .startListening(widget.mainPage.speechRecognitionPage.speech),
                                    child: const Icon(Icons.mic, size: (30)),
                                  ))))
                    ],
                  )))
          : DigitalInkPage(mainPage: widget.mainPage),
      Container(
          padding: const EdgeInsets.symmetric(vertical: 5, horizontal: 10),
          child: Column(children: [
            showControls
                ? Container(
                    padding: const EdgeInsets.all(5.0),
                    decoration:
                        BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
                    child: Row(
                        mainAxisAlignment: MainAxisAlignment.spaceAround,
                        crossAxisAlignment: CrossAxisAlignment.center,
                        children: [
                          const Icon(Icons.speed),
                          Slider(
                            value: currentSpeedValue,
                            min: 0,
                            max: 100,
                            divisions: 20,
                            label: '${currentSpeedValue.round()} %',
                            onChanged: connectedMQTT || connectedBluetooth
                                ? (value) => setState(() => currentSpeedValue = value)
                                : null,
                            onChangeEnd: (value) {
                              speedHandler = value > sliderSpeedValue ? 'quick' : 'slow';
                              setState(() => sliderSpeedValue = value);
                              setAction({
                                'control': 'velocidade',
                                'value': value.round(),
                                'handling': speedHandler,
                                'action': 'speed'
                              });
                            },
                          )
                        ]))
                : Container(),
            Text(S().controls_voice_label),
            Container(
                padding: const EdgeInsets.all(5.0),
                decoration:
                    BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
                child: Column(children: [
                  Row(
                      mainAxisAlignment: MainAxisAlignment.spaceAround,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        const Icon(Icons.language),
                        DropdownButton<String>(
                          value: currentLocaleId,
                          underline: Container(
                            height: 0,
                          ),
                          onChanged: connectedMQTT || connectedBluetooth
                              ? (selectedVal) =>
                                  textToSpeechManager.tts.getLanguageCodeByName(selectedVal!).then((value) {
                                    textToSpeechManager.tts.setLanguage(value!);
                                    setState(() => currentLocaleId = selectedVal);
                                  })
                              : null,
                          items: localeNames.map<DropdownMenuItem<String>>((String value) {
                            return DropdownMenuItem<String>(
                              value: value,
                              child: Text(value),
                            );
                          }).toList(),
                        )
                      ]),
                  Row(
                      mainAxisAlignment: MainAxisAlignment.spaceAround,
                      crossAxisAlignment: CrossAxisAlignment.center,
                      children: [
                        const Icon(Icons.volume_up),
                        Slider(
                          value: volume,
                          min: 0,
                          max: 1.0,
                          divisions: 10,
                          label: volume.toString(),
                          onChanged: connectedMQTT || connectedBluetooth ? (value) => onChangedVolume(value) : null,
                        )
                      ])
                ])),
          ]))
    ]);
  }
}
