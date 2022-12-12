import 'package:andarilho/utility/text_to_%20speech_manager.dart';
import 'package:flutter/services.dart';
import 'package:yaml/yaml.dart';

class ProcessSpeechCommand {
  var yalmControls;
  TextToSpeechManager textToSpeechManager = TextToSpeechManager();

  late var device;
  late final exitCommand;
  late final speedCommand;
  late final controlCommand;
  late Map<String, int> speedControl = {'value': 30, 'min': 0, 'max': 100};

  bool deviceActive = false;

  ProcessSpeechCommand() {
    rootBundle
        .loadString('assets/files/controls.yaml')
        .then((value) => yalmControls = loadYaml(value))
        .whenComplete(() {
      device = yalmControls['device'];
      exitCommand = yalmControls['exit'];
      speedCommand = yalmControls['speed'];
      controlCommand = yalmControls['command'];
      deviceActive = true;
    });
  }

  bool executeCommand(command, commands) {
    return <String>{...commands}.intersection(<String>{...command}).isNotEmpty;
  }

  Map<String, dynamic> sendCommand(newSpeed, String command) {
    Map<String, dynamic> result = {'control': 'undefined', 'value': 0, 'handling': 'undefined', 'action': 'undefined'};
    // Checks if the device identifier has been provided
    if (executeCommand(device['name'], command.split(' '))) {
      bool exit = executeCommand(exitCommand['control'], command.split(' '));
      bool validCommand = false;
      if (!exit) {
        // Process device directional commands
        for (final control in controlCommand.keys) {
          if (executeCommand(controlCommand[control]['control'], command.split(' '))) {
            if (controlCommand[control]['value'] > 0) {
              result = {
                'control': 'controle',
                'value': controlCommand[control]['value'],
                'handling': control,
                'action': 'command'
              };
            } else {
              device['manual'] = controlCommand[command]['value'] == -2;
            }
            speakCommand(controlCommand[control]['speech']);
            validCommand = true;
          }
        }
        // Process device speed control
        for (final speed in speedCommand.keys) {
          if (executeCommand(speedCommand[speed]['control'], command.split(' '))) {
            speedControl['value'] = newSpeed.toInt() + speedCommand[speed]['value'];
            bool warning = false;
            if (speedControl['value']! < speedControl['min']!) {
              speedControl['value'] = speedControl['min']!;
              warning = true;
            }
            if (speedControl['value']! > speedControl['max']!) {
              speedControl['value'] = speedControl['max']!;
              warning = true;
            }
            if (!warning) {
              speakCommand(speedCommand[speed]['speech']);
            } else {
              speakCommand(speedCommand[speed]['warning']);
            }
            validCommand = true;
            result = {
              'control': 'velocidade',
              'value': speedControl['value'],
              'handling': speed,
              'action': 'speed'
            };
          }
        }
        if (!validCommand) {
          speakCommand(device['invalid']);
        }
      } else {
        // Informs that the device will no longer be used
        speakCommand(exitCommand['speech']);
      }
    } else {
      // Informs that the device name was not provided
      speakCommand(device['warning']);
    }
    return result;
  }

  void speakCommand(text) {
    textToSpeechManager.tts.speak(text);
  }
}
