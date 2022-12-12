import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';

import 'package:andarilho/generated/l10n.dart';
import 'package:andarilho/screens/main_page/main_page.dart';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';

class BluetoothConfigurationPage extends StatefulWidget {
  final MainPage mainPage;
  BluetoothConfigurationPage({Key? key, required this.mainPage}) : super(key: key);

  BluetoothConfigurationPageState bluetoothConfigurationPageState = BluetoothConfigurationPageState();

  get bluetoothConnection => bluetoothConfigurationPageState.bluetoothConnection;
  get deviceConnected => bluetoothConfigurationPageState.deviceConnected;

  @override
  BluetoothConfigurationPageState createState() => bluetoothConfigurationPageState;
}

class BluetoothConfigurationPageState extends State<BluetoothConfigurationPage> {
  BluetoothState bluetoothState = BluetoothState.UNKNOWN;
  List<BluetoothDevice> bondedDevices = List<BluetoothDevice>.empty(growable: true);

  String deviceName = '';
  BluetoothConnection? bluetoothConnection;
  Map<String, dynamic> deviceConnected = {'connected': false, 'index': -1, 'address': ''};

  @override
  void initState() {
    super.initState();
    FlutterBluetoothSerial.instance.state.then((state) => setState(() => bluetoothState = state));
    FlutterBluetoothSerial.instance.name.then((name) => setState(() => deviceName = name!));
    FlutterBluetoothSerial.instance.getBondedDevices().then((devices) => bondedDevices = devices);
  }

  @override
  void dispose() {
    super.dispose();
  }

  Future<void> connectDevice(int index) async {
    BluetoothConnection.toAddress(bondedDevices[index].address).then((value) {
      bluetoothConnection = value;
      bluetoothConnection?.output.allSent.whenComplete(() {
        bluetoothConnection!.output.add(Uint8List.fromList(utf8.encode('${S().handshake_message} - $deviceName\r\n')));
        setState(() => deviceConnected = {'connected': true, 'index': index, 'address': bondedDevices[index].address});
        widget.mainPage.controlPage.setEnvironmentState();
        widget.mainPage.speechRecognitionPage.setEnvironmentState();
        widget.mainPage.onPageTapped(0);
        ScaffoldMessenger.of(context).showSnackBar(SnackBar(
          content: Text('${S().handshake_message} ${bondedDevices[index].name}'),
        ));
      });
    }).catchError((e) {
      print(e);
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(
        content: Text('${S().handshake_error} ${bondedDevices[index].name}'),
      ));
    });
  }

  void disconnectDevice(int index) {
    bluetoothConnection?.output.allSent.whenComplete(() {
      bluetoothConnection?.output.add(Uint8List.fromList(utf8.encode('${S().handshake_disconnect} - $deviceName\r\n')));
      bluetoothConnection?.dispose();
      bluetoothConnection = null;
      setState(() => deviceConnected = {'connected': false, 'index': index, 'address': ''});
      widget.mainPage.controlPage.setEnvironmentState();
      widget.mainPage.speechRecognitionPage.setEnvironmentState();
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(
        content: Text('${S().handshake_disconnect} ${bondedDevices[index].name}'),
      ));
    });
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
          child: Text(
            S().bluetooth_title,
          ),
          onPressed: () {},
        ),
        const Expanded(child: Divider(endIndent: 10)),
      ]),
      Container(
          margin: const EdgeInsets.only(left: 10, right: 10, top: 5),
          padding: const EdgeInsets.all(5),
          decoration: BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
          child: Column(children: [
            SwitchListTile(
              title: Text(S().enable_bluetooth_label),
              value: bluetoothState.isEnabled,
              secondary: const Icon(Icons.settings_bluetooth),
              onChanged: (enabled) {
                future() async {
                  if (enabled) {
                    await FlutterBluetoothSerial.instance.requestEnable();
                  } else {
                    await FlutterBluetoothSerial.instance.requestDisable();
                  }
                }

                future().then((_) =>
                    FlutterBluetoothSerial.instance.state.then((state) => setState(() => bluetoothState = state)));
              },
            ),
            ListTile(
                leading: const Icon(Icons.settings_rounded),
                title: Text(S().config_bluetooth_label),
                //subtitle: Text(bluetoothState.toString()),
                trailing: const Icon(Icons.more_vert),
                onTap: () => FlutterBluetoothSerial.instance.openSettings()),
            ListTile(
              leading: const Icon(Icons.phone_android),
              title: Text(deviceName),
            ),
          ])),
      ListTile(title: Center(child: Text(S().list_bluetooth_label.toUpperCase())), subtitle: Center(child: Text(S().paired_label))),
      Expanded(
          child: Container(
              margin: const EdgeInsets.only(left: 10, right: 10, bottom: 40),
              padding: const EdgeInsets.all(5),
              decoration:
                  BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
              child: ListView.builder(
                  itemCount: bondedDevices.length,
                  itemBuilder: (BuildContext context, int index) {
                    return ListTile(
                        leading: const Icon(Icons.settings_remote),
                        title: Text('${bondedDevices[index].name}'),
                        trailing: deviceConnected['connected'] && deviceConnected['index'] == index
                            ? Icon(
                                Icons.phonelink,
                                color: Colors.blue.shade400,
                              )
                            : const Icon(Icons.phonelink_off),
                        onTap: () => !deviceConnected['connected'] ? connectDevice(index) : null,
                        onLongPress: () => disconnectDevice(index));
                  })))
    ]);
  }
}
