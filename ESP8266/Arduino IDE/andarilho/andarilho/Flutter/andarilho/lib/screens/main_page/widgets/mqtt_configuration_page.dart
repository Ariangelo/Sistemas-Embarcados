import 'package:andarilho/generated/l10n.dart';
import 'package:andarilho/screens/main_page/main_page.dart';
import 'package:andarilho/utility/mqtt_manager.dart';
import 'package:andarilho/widget/custom_elevated_button.dart';
import 'package:andarilho/widget/custom_text_field.dart';
import 'package:flutter/material.dart';
import 'package:mqtt_client/mqtt_client.dart';
import 'package:shared_preferences/shared_preferences.dart';

class MQTTConfigurationPage extends StatefulWidget {
  final MainPage mainPage;
  MQTTConfigurationPage({Key? key, required this.mainPage}) : super(key: key);

  MQTTConfigurationPageState mqttConfigurationPageState = MQTTConfigurationPageState();

  get mqttClientManager => mqttConfigurationPageState.mqttClientManager;
  get connectedMQTT => mqttConfigurationPageState.connectedMQTT;

  @override
  MQTTConfigurationPageState createState() => mqttConfigurationPageState;
}

class MQTTConfigurationPageState extends State<MQTTConfigurationPage> {
  final formKey = GlobalKey<FormState>();
  TextEditingController controllerServer = TextEditingController();
  TextEditingController controllerPort = TextEditingController();
  TextEditingController controllerClient = TextEditingController();
  TextEditingController controllerTopic = TextEditingController();

  late List<String> mqttBroker;
  bool connectedMQTT = false;
  MQTTManager mqttClientManager = MQTTManager(server: '', client: '', port: '-1');

  @override
  void initState() {
    super.initState();
    SharedPreferences.getInstance().then((value) {
      mqttBroker = value.getStringList('mqttBroker') ??
          ['broker.mqtt-dashboard.com', '1883', 'flutter-robo-Ariangelo', 'embarcados.controle.robo.payload'];
      controllerServer.text = mqttBroker[0];
      controllerPort.text = mqttBroker[1];
      controllerClient.text = mqttBroker[2];
      controllerTopic.text = mqttBroker[3];
    }).whenComplete(() {
      mqttClientManager =
          MQTTManager(server: controllerServer.text, client: controllerClient.text, port: controllerPort.text);
      connectedMQTT = mqttClientManager.connectionState() == MqttConnectionState.connected;
    });
  }

  @override
  void dispose() {
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Form(
        key: formKey,
        child: SingleChildScrollView(
            child: Column(
          children: [
            Row(mainAxisAlignment: MainAxisAlignment.spaceBetween, children: [
              const Expanded(child: Divider(indent: 10)),
              OutlinedButton(
                  style: ButtonStyle(
                      shape: MaterialStateProperty.all<RoundedRectangleBorder>(RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(30.0),
                  ))),
                  onPressed: () {},
                  child: Text(
                    S().mqtt_title,
                  )),
              const Expanded(child: Divider(endIndent: 10)),
            ]),
            Container(
              margin: const EdgeInsets.only(left: 10, right: 10, top: 20),
              //padding: const EdgeInsets.all(5),
              decoration:
                  BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
              child: Column(children: [
                CustomTextField(
                  padding: 10,
                  labelText: S().mqtt_server_labelText,
                  controller: controllerServer,
                  prefixIcon: const Icon(Icons.router),
                  //onSaved: (val) => setState(() => widget.user.info = val!),
                ),
                CustomTextField(
                  padding: 10,
                  labelText: S().mqtt_port_labelText,
                  controller: controllerPort,
                  prefixIcon: const Icon(Icons.meeting_room),
                  //onSaved: (val) => setState(() => widget.user.info = val!),
                ),
                CustomTextField(
                  padding: 10,
                  labelText: S().mqtt_client_labelText,
                  controller: controllerClient,
                  prefixIcon: const Icon(Icons.account_box),
                  //onSaved: (val) => setState(() => widget.user.info = val!),
                ),
                CustomTextField(
                  padding: 10,
                  labelText: S().mqtt_topic_labelText,
                  controller: controllerTopic,
                  prefixIcon: const Icon(Icons.topic),
                  //onSaved: (val) => setState(() => widget.user.info = val!),
                )
              ]),
            ),
            Container(
                alignment: FractionalOffset.center,
                padding: const EdgeInsets.only(top: 40),
                child: Row(mainAxisAlignment: MainAxisAlignment.center, children: [
                  CustomElevatedButton(
                    padding: const EdgeInsets.all(10),
                    label: S().mqtt_btnConnect_label,
                    icon: const Icon(Icons.check_circle),
                    width: 180,
                    onPressed: !connectedMQTT
                        ? () {
                            if (formKey.currentState!.validate()) {
                              formKey.currentState!.save();
                              mqttClientManager.server = controllerServer.text;
                              mqttClientManager.client = controllerClient.text;
                              mqttClientManager.port = controllerPort.text;
                              mqttClientManager.topic = controllerTopic.text;
                              mqttBroker = [
                                controllerServer.text,
                                controllerPort.text,
                                controllerClient.text,
                                controllerTopic.text
                              ];
                              mqttClientManager.connect().whenComplete(() {
                                setState(() => connectedMQTT = true);
                                SharedPreferences.getInstance()
                                    .then((value) => value.setStringList('mqttBroker', mqttBroker));
                                widget.mainPage.controlPage.setEnvironmentState();
                                widget.mainPage.speechRecognitionPage.setEnvironmentState();
                                widget.mainPage.onPageTapped(0);
                              });
                            }
                          }
                        : null,
                  ),
                  CustomElevatedButton(
                    padding: const EdgeInsets.all(10),
                    label: S().mqtt_btnDisconnect_label,
                    icon: const Icon(Icons.cancel),
                    color: Colors.redAccent,
                    width: 180,
                    onPressed: connectedMQTT
                        ? () {
                            mqttClientManager.disconnect();
                            setState(() => connectedMQTT = false);
                            widget.mainPage.controlPage.setEnvironmentState();
                            widget.mainPage.speechRecognitionPage.setEnvironmentState();
                          }
                        : null,
                  ),
                ]))
          ],
        )));
  }
}
