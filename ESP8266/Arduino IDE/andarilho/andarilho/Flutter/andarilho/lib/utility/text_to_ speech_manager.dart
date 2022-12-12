import 'package:text_to_speech/text_to_speech.dart';

class TextToSpeechManager {
  late TextToSpeech tts;

  String voice = '';
  double volume = 0.5; // Range: 0-1
  double rate = 1.0; // Range: 0-2
  double pitch = 1.0; // Range: 0-2

  String defaultLocaleId = 'en-US';
  late String currentLocaleId;
  late String localeId;
  late List<String> localeIdList;
  late List<String> localeNames;

  TextToSpeechManager() {
    tts = TextToSpeech();
  }

  Future<dynamic> updateLocales() async {
    return tts
        .getLanguages()
        .then((value) => localeIdList = value)
        .whenComplete(() => tts.getDisplayLanguages().then((value) => localeNames = value!))
        .whenComplete(() => tts
            .getDefaultLanguage()
            .then((value) =>
                value != null && localeIdList.contains(value) ? localeId = value : localeId = defaultLocaleId)
            .whenComplete(
                () => tts.getDisplayLanguageByCode(localeId).then((value) => currentLocaleId = value!).whenComplete(() {
                      tts.setVolume(volume);
                      tts.setRate(rate);
                      tts.setLanguage(localeId);
                      tts.setPitch(pitch);
                    })));
  }

  Future<String?> getVoiceByLang(String lang) async {
    final List<String>? voices = await tts.getVoiceByLang(lang);
    print(voices);
    if (voices != null && voices.isNotEmpty) {
      return voices.first;
    }
    return null;
  }

  void speak(text) {
    tts.speak(text);
  }
}
