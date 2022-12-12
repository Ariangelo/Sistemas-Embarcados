// DO NOT EDIT. This is code generated via package:intl/generate_localized.dart
// This is a library that provides messages for a pt_BR locale. All the
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
  String get localeName => 'pt_BR';

  final messages = _notInlinedMessages(_notInlinedMessages);
  static Map<String, Function> _notInlinedMessages(_) => <String, Function>{
        "bluetooth_label": MessageLookupByLibrary.simpleMessage("Bluetooth"),
        "bluetooth_title":
            MessageLookupByLibrary.simpleMessage("Configuração Bluetooth"),
        "config_bluetooth_label":
            MessageLookupByLibrary.simpleMessage("Configurar Bluetooth"),
        "controls_label": MessageLookupByLibrary.simpleMessage("Controles"),
        "controls_title":
            MessageLookupByLibrary.simpleMessage("Controles do Robô"),
        "controls_voice_label":
            MessageLookupByLibrary.simpleMessage("Resposta por Voz"),
        "enable_bluetooth_label":
            MessageLookupByLibrary.simpleMessage("Habilitar Bluetooth"),
        "exit_message": MessageLookupByLibrary.simpleMessage(
            "Pressione o botão Voltar novamente para sair"),
        "handshake_disconnect":
            MessageLookupByLibrary.simpleMessage("Desconectado do dispositivo"),
        "handshake_error": MessageLookupByLibrary.simpleMessage(
            "Erro ao conectar com o dispositivo"),
        "handshake_message":
            MessageLookupByLibrary.simpleMessage("Conectado ao dispositivo"),
        "list_bluetooth_label":
            MessageLookupByLibrary.simpleMessage("Dispositivos"),
        "mqtt_btnConnect_label":
            MessageLookupByLibrary.simpleMessage("Conectar"),
        "mqtt_btnDisconnect_label":
            MessageLookupByLibrary.simpleMessage("Desconectar"),
        "mqtt_client_labelText":
            MessageLookupByLibrary.simpleMessage("Cliente"),
        "mqtt_label": MessageLookupByLibrary.simpleMessage("MQTT"),
        "mqtt_port_labelText": MessageLookupByLibrary.simpleMessage("Porta"),
        "mqtt_server_labelText":
            MessageLookupByLibrary.simpleMessage("Servidor"),
        "mqtt_title": MessageLookupByLibrary.simpleMessage("Configuração MQTT"),
        "mqtt_topic_labelText": MessageLookupByLibrary.simpleMessage("Tópico"),
        "paired_label": MessageLookupByLibrary.simpleMessage("pareados"),
        "title": MessageLookupByLibrary.simpleMessage("Andarilho"),
        "voice_exit_message": MessageLookupByLibrary.simpleMessage(
            "Finalizar utilização do controle por voz"),
        "voice_label": MessageLookupByLibrary.simpleMessage("Voz"),
        "voice_receiving_message":
            MessageLookupByLibrary.simpleMessage("Recebendo o comando"),
        "voice_recognition_failed": MessageLookupByLibrary.simpleMessage(
            "Falha no reconhecimento de voz"),
        "voice_start_message": MessageLookupByLibrary.simpleMessage(
            "Pressione para ativar o controle por voz"),
        "voice_title": MessageLookupByLibrary.simpleMessage("Controle por Voz"),
        "voice_waiting_message":
            MessageLookupByLibrary.simpleMessage("Aguardando o comando"),
        "warning_conection_message": MessageLookupByLibrary.simpleMessage(
            "É necessário uma conexão MQTT ou Bluetooth")
      };
}
