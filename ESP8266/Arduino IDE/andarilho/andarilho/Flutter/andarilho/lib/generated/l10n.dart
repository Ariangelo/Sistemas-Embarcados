// GENERATED CODE - DO NOT MODIFY BY HAND
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'intl/messages_all.dart';

// **************************************************************************
// Generator: Flutter Intl IDE plugin
// Made by Localizely
// **************************************************************************

// ignore_for_file: non_constant_identifier_names, lines_longer_than_80_chars
// ignore_for_file: join_return_with_assignment, prefer_final_in_for_each
// ignore_for_file: avoid_redundant_argument_values, avoid_escaping_inner_quotes

class S {
  S();

  static S? _current;

  static S get current {
    assert(_current != null,
        'No instance of S was loaded. Try to initialize the S delegate before accessing S.current.');
    return _current!;
  }

  static const AppLocalizationDelegate delegate = AppLocalizationDelegate();

  static Future<S> load(Locale locale) {
    final name = (locale.countryCode?.isEmpty ?? false)
        ? locale.languageCode
        : locale.toString();
    final localeName = Intl.canonicalizedLocale(name);
    return initializeMessages(localeName).then((_) {
      Intl.defaultLocale = localeName;
      final instance = S();
      S._current = instance;

      return instance;
    });
  }

  static S of(BuildContext context) {
    final instance = S.maybeOf(context);
    assert(instance != null,
        'No instance of S present in the widget tree. Did you add S.delegate in localizationsDelegates?');
    return instance!;
  }

  static S? maybeOf(BuildContext context) {
    return Localizations.of<S>(context, S);
  }

  /// `Andarilho`
  String get title {
    return Intl.message(
      'Andarilho',
      name: 'title',
      desc: '',
      args: [],
    );
  }

  /// `Controls`
  String get controls_label {
    return Intl.message(
      'Controls',
      name: 'controls_label',
      desc: '',
      args: [],
    );
  }

  /// `Robot controls`
  String get controls_title {
    return Intl.message(
      'Robot controls',
      name: 'controls_title',
      desc: '',
      args: [],
    );
  }

  /// `Voice answer`
  String get controls_voice_label {
    return Intl.message(
      'Voice answer',
      name: 'controls_voice_label',
      desc: '',
      args: [],
    );
  }

  /// `MQTT`
  String get mqtt_label {
    return Intl.message(
      'MQTT',
      name: 'mqtt_label',
      desc: '',
      args: [],
    );
  }

  /// `MQTT Configuration`
  String get mqtt_title {
    return Intl.message(
      'MQTT Configuration',
      name: 'mqtt_title',
      desc: '',
      args: [],
    );
  }

  /// `Server`
  String get mqtt_server_labelText {
    return Intl.message(
      'Server',
      name: 'mqtt_server_labelText',
      desc: '',
      args: [],
    );
  }

  /// `Port`
  String get mqtt_port_labelText {
    return Intl.message(
      'Port',
      name: 'mqtt_port_labelText',
      desc: '',
      args: [],
    );
  }

  /// `Client`
  String get mqtt_client_labelText {
    return Intl.message(
      'Client',
      name: 'mqtt_client_labelText',
      desc: '',
      args: [],
    );
  }

  /// `Topic`
  String get mqtt_topic_labelText {
    return Intl.message(
      'Topic',
      name: 'mqtt_topic_labelText',
      desc: '',
      args: [],
    );
  }

  /// `Connect`
  String get mqtt_btnConnect_label {
    return Intl.message(
      'Connect',
      name: 'mqtt_btnConnect_label',
      desc: '',
      args: [],
    );
  }

  /// `Disconnect`
  String get mqtt_btnDisconnect_label {
    return Intl.message(
      'Disconnect',
      name: 'mqtt_btnDisconnect_label',
      desc: '',
      args: [],
    );
  }

  /// `Disconnected from device`
  String get handshake_disconnect {
    return Intl.message(
      'Disconnected from device',
      name: 'handshake_disconnect',
      desc: '',
      args: [],
    );
  }

  /// `Enable Bluetooth`
  String get enable_bluetooth_label {
    return Intl.message(
      'Enable Bluetooth',
      name: 'enable_bluetooth_label',
      desc: '',
      args: [],
    );
  }

  /// `Config Bluetooth`
  String get config_bluetooth_label {
    return Intl.message(
      'Config Bluetooth',
      name: 'config_bluetooth_label',
      desc: '',
      args: [],
    );
  }

  /// `Devices`
  String get list_bluetooth_label {
    return Intl.message(
      'Devices',
      name: 'list_bluetooth_label',
      desc: '',
      args: [],
    );
  }

  /// `paired`
  String get paired_label {
    return Intl.message(
      'paired',
      name: 'paired_label',
      desc: '',
      args: [],
    );
  }

  /// `Bluetooth`
  String get bluetooth_label {
    return Intl.message(
      'Bluetooth',
      name: 'bluetooth_label',
      desc: '',
      args: [],
    );
  }

  /// `Bluetooth Configuration`
  String get bluetooth_title {
    return Intl.message(
      'Bluetooth Configuration',
      name: 'bluetooth_title',
      desc: '',
      args: [],
    );
  }

  /// `Conneceted to device`
  String get handshake_message {
    return Intl.message(
      'Conneceted to device',
      name: 'handshake_message',
      desc: '',
      args: [],
    );
  }

  /// `Error to connect with device`
  String get handshake_error {
    return Intl.message(
      'Error to connect with device',
      name: 'handshake_error',
      desc: '',
      args: [],
    );
  }

  /// `Voice`
  String get voice_label {
    return Intl.message(
      'Voice',
      name: 'voice_label',
      desc: '',
      args: [],
    );
  }

  /// `Voice control`
  String get voice_title {
    return Intl.message(
      'Voice control',
      name: 'voice_title',
      desc: '',
      args: [],
    );
  }

  /// `Press to activate voice control`
  String get voice_start_message {
    return Intl.message(
      'Press to activate voice control',
      name: 'voice_start_message',
      desc: '',
      args: [],
    );
  }

  /// `End using voice control`
  String get voice_exit_message {
    return Intl.message(
      'End using voice control',
      name: 'voice_exit_message',
      desc: '',
      args: [],
    );
  }

  /// `Getting the command`
  String get voice_receiving_message {
    return Intl.message(
      'Getting the command',
      name: 'voice_receiving_message',
      desc: '',
      args: [],
    );
  }

  /// `Waiting the command`
  String get voice_waiting_message {
    return Intl.message(
      'Waiting the command',
      name: 'voice_waiting_message',
      desc: '',
      args: [],
    );
  }

  /// `Speech recognition failed`
  String get voice_recognition_failed {
    return Intl.message(
      'Speech recognition failed',
      name: 'voice_recognition_failed',
      desc: '',
      args: [],
    );
  }

  /// `MQTT or Bluetooth connection is required`
  String get warning_conection_message {
    return Intl.message(
      'MQTT or Bluetooth connection is required',
      name: 'warning_conection_message',
      desc: '',
      args: [],
    );
  }

  /// `Press the back button again to exit`
  String get exit_message {
    return Intl.message(
      'Press the back button again to exit',
      name: 'exit_message',
      desc: '',
      args: [],
    );
  }
}

class AppLocalizationDelegate extends LocalizationsDelegate<S> {
  const AppLocalizationDelegate();

  List<Locale> get supportedLocales {
    return const <Locale>[
      Locale.fromSubtags(languageCode: 'en'),
      Locale.fromSubtags(languageCode: 'en', countryCode: 'US'),
      Locale.fromSubtags(languageCode: 'pt', countryCode: 'BR'),
    ];
  }

  @override
  bool isSupported(Locale locale) => _isSupported(locale);
  @override
  Future<S> load(Locale locale) => S.load(locale);
  @override
  bool shouldReload(AppLocalizationDelegate old) => false;

  bool _isSupported(Locale locale) {
    for (var supportedLocale in supportedLocales) {
      if (supportedLocale.languageCode == locale.languageCode) {
        return true;
      }
    }
    return false;
  }
}
