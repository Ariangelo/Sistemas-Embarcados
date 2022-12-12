// DO NOT EDIT. This is code generated via package:intl/generate_localized.dart
// This is a library that provides messages for a en_US locale. All the
// messages from the main program should be duplicated here with the same
// function name.

// Ignore issues from commonly used lints in this file.
// ignore_for_file:unnecessary_brace_in_string_interps, unnecessary_new
// ignore_for_file:prefer_single_quotes,comment_references, directives_ordering
// ignore_for_file:annotate_overrides,prefer_generic_function_type_aliases
// ignore_for_file:unused_import, file_names, avoid_escaping_inner_quotes
// ignore_for_file:unnecessary_string_interpolations, unnecessary_string_escapes

import 'package:intl/intl.dart';
import 'package:intl/message_lookup_by_library.dart';

final messages = new MessageLookup();

typedef String MessageIfAbsent(String messageStr, List<dynamic> args);

class MessageLookup extends MessageLookupByLibrary {
  String get localeName => 'en_US';

  final messages = _notInlinedMessages(_notInlinedMessages);
  static Map<String, Function> _notInlinedMessages(_) => <String, Function>{
        "bluetooth_label": MessageLookupByLibrary.simpleMessage("Bluetooth"),
        "bluetooth_title":
            MessageLookupByLibrary.simpleMessage("Bluetooth Configuration"),
        "config_bluetooth_label":
            MessageLookupByLibrary.simpleMessage("Config Bluetooth"),
        "controls_label": MessageLookupByLibrary.simpleMessage("Controls"),
        "controls_title":
            MessageLookupByLibrary.simpleMessage("Robot controls"),
        "controls_voice_label":
            MessageLookupByLibrary.simpleMessage("Voice answer"),
        "enable_bluetooth_label":
            MessageLookupByLibrary.simpleMessage("Enable Bluetooth"),
        "exit_message": MessageLookupByLibrary.simpleMessage(
            "Press the back button again to exit"),
        "handshake_disconnect":
            MessageLookupByLibrary.simpleMessage("Disconnected from device"),
        "handshake_error": MessageLookupByLibrary.simpleMessage(
            "Error to connect with device"),
        "handshake_message":
            MessageLookupByLibrary.simpleMessage("Conneceted to device"),
        "list_bluetooth_label": MessageLookupByLibrary.simpleMessage("Devices"),
        "mqtt_btnConnect_label":
            MessageLookupByLibrary.simpleMessage("Connect"),
        "mqtt_btnDisconnect_label":
            MessageLookupByLibrary.simpleMessage("Disconnect"),
        "mqtt_client_labelText": MessageLookupByLibrary.simpleMessage("Client"),
        "mqtt_label": MessageLookupByLibrary.simpleMessage("MQTT"),
        "mqtt_port_labelText": MessageLookupByLibrary.simpleMessage("Port"),
        "mqtt_server_labelText": MessageLookupByLibrary.simpleMessage("Server"),
        "mqtt_title":
            MessageLookupByLibrary.simpleMessage("MQTT Configuration"),
        "mqtt_topic_labelText": MessageLookupByLibrary.simpleMessage("Topic"),
        "paired_label": MessageLookupByLibrary.simpleMessage("paired"),
        "title": MessageLookupByLibrary.simpleMessage("Andarilho"),
        "voice_exit_message":
            MessageLookupByLibrary.simpleMessage("End using voice control"),
        "voice_label": MessageLookupByLibrary.simpleMessage("Voice"),
        "voice_receiving_message":
            MessageLookupByLibrary.simpleMessage("Getting the command"),
        "voice_recognition_failed":
            MessageLookupByLibrary.simpleMessage("Speech recognition failed"),
        "voice_start_message": MessageLookupByLibrary.simpleMessage(
            "Press to activate voice control"),
        "voice_title": MessageLookupByLibrary.simpleMessage("Voice control"),
        "voice_waiting_message":
            MessageLookupByLibrary.simpleMessage("Waiting the command"),
        "warning_conection_message": MessageLookupByLibrary.simpleMessage(
            "MQTT or Bluetooth connection is required")
      };
}
