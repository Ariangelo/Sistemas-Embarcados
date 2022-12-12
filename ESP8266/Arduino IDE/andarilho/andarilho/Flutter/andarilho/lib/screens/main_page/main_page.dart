import 'package:andarilho/generated/l10n.dart';
import 'package:andarilho/screens/main_page/widgets/bluetooth_configuration_page.dart';
import 'package:andarilho/screens/main_page/widgets/controls_page.dart';
import 'package:andarilho/screens/main_page/widgets/mqtt_configuration_page.dart';
import 'package:andarilho/screens/main_page/widgets/speech_recognition_page.dart';
import 'package:flutter/material.dart';

class MainPage extends StatefulWidget {
  final String title;
  late final ControlsPage controlPage;
  late final MQTTConfigurationPage mqttConfigurationPage;
  late final BluetoothConfigurationPage bluetoothConfigurationPage;
  late final SpeechRecognitionPage speechRecognitionPage;
  MainPage({Key? key, required this.title}) : super(key: key) {
    controlPage = ControlsPage(mainPage: this);
    mqttConfigurationPage = MQTTConfigurationPage(mainPage: this);
    bluetoothConfigurationPage = BluetoothConfigurationPage(mainPage: this);
    speechRecognitionPage = SpeechRecognitionPage(mainPage: this);
  }

  get selectedPage => mainPageState.selectedPage;

  void onPageTapped(int index) {
    mainPageState.onPageTapped(index);
  }

  final MainPageState mainPageState = MainPageState();

  @override
  State<MainPage> createState() => mainPageState;
}

class MainPageState extends State<MainPage> {
  DateTime currentTime = DateTime.now();
  int selectedPage = 0;
  late final List<Widget> widgetPages;

  @override
  void initState() {
    super.initState();
    widgetPages = [
      widget.controlPage,
      widget.mqttConfigurationPage,
      widget.bluetoothConfigurationPage,
      widget.speechRecognitionPage
    ];
  }

  @override
  void dispose() {
    super.dispose();
  }

  void onPageTapped(int index) {
    setState(() => selectedPage = index);
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Center(child: Text(widget.title)),
      ),
      body: WillPopScope(
        onWillPop: () {
          DateTime now = DateTime.now();
          if (now.difference(currentTime) > const Duration(seconds: 2)) {
            currentTime = now;
            ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text(S().exit_message)));
            return Future.value(false);
          }
          return Future.value(true);
        },
        child: IndexedStack(
          index: selectedPage,
          children: widgetPages,
        ),
      ),
      bottomNavigationBar: BottomNavigationBar(
        type: BottomNavigationBarType.fixed,
        items: <BottomNavigationBarItem>[
          BottomNavigationBarItem(
            icon: Icon(Icons.tune),
            label: S().controls_label,
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.sensors),
            label: S().mqtt_label,
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.bluetooth),
            label: S().bluetooth_label,
          ),
          BottomNavigationBarItem(
            icon: Icon(Icons.keyboard_voice),
            label: S().voice_label,
          ),
        ],
        currentIndex: selectedPage,
        selectedItemColor: Colors.amber[800],
        onTap: onPageTapped,
      ),
    );
  }
}
