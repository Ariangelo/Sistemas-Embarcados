import 'dart:typed_data';

import 'package:mqtt_client/mqtt_client.dart';
import 'package:mqtt_client/mqtt_server_client.dart';

class MQTTManager {
  String server;
  String client;
  String port;
  String? topic;

  late MqttServerClient mqttClient;

  MQTTManager({required this.server, required this.client, required this.port}) {
    mqttClient = MqttServerClient.withPort(server, client, int.parse(port));
  }

  Future<bool> connect() {
    //mqttClient.logging(on: true);MqttConnectionState
    mqttClient.keepAlivePeriod = 60;
    mqttClient.onConnected = onConnected;
    mqttClient.onDisconnected = onDisconnected;
    //mqttClient.onSubscribed = onSubscribed;
    //mqttClient.pongCallback = pong;
    Future<bool> result = Future.value(false);
    mqttClient.connect().whenComplete(() {
      mqttClient.connectionMessage = MqttConnectMessage().startClean();
      result = Future.value(true);
    }).catchError((e) {
      print('MQTTClient::Client exception - $e');
      mqttClient.disconnect();
      result = Future<bool>.value(false);
    });
    return result;
    /*
    final connMessage = MqttConnectMessage().startClean();
    mqttClient.connectionMessage = connMessage;
    try {
      await mqttClient.connect();
    } on NoConnectionException catch (e) {
      print('MQTTClient::Client exception - $e');
      mqttClient.disconnect();
    } on SocketException catch (e) {
      print('MQTTClient::Socket exception - $e');
      mqttClient.disconnect();
    }

    return 0;

     */
  }

  void disconnect() {
    mqttClient.disconnect();
  }

  MqttConnectionState? connectionState() {
    return mqttClient.connectionStatus?.state;
  }

  void subscribe(String topic) {
    mqttClient.subscribe(topic, MqttQos.atLeastOnce);
  }

  void onConnected() {
    print('MQTTClient -> Connected');
  }

  void onDisconnected() {
    print('MQTTClient -> Disconnected');
  }

  void onSubscribed(String topic) {
    print('MQTTClient::Subscribed to topic: $topic');
  }

  void pong() {
    print('MQTTClient::Ping response received');
  }

  void publishMessage(String topic, Uint8List message) {
    final builder = MqttClientPayloadBuilder();
    builder.addString(String.fromCharCodes(message));
    mqttClient.publishMessage(topic, MqttQos.exactlyOnce, builder.payload!);
  }

  Stream<List<MqttReceivedMessage<MqttMessage>>>? getMessagesStream() {
    return mqttClient.updates;
  }
}
