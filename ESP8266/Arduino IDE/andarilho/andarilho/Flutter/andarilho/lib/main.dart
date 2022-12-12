import 'dart:io';

import 'package:andarilho/generated/l10n.dart';
import 'package:desktop_window/desktop_window.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_localizations/flutter_localizations.dart';

import 'screens/main_page/main_page.dart';

void main() {
  WidgetsFlutterBinding.ensureInitialized();
  if (Platform.isWindows || Platform.isLinux || Platform.isMacOS) {
    Size size = const Size(525, 1000);
    DesktopWindow.setWindowSize(size);
    DesktopWindow.setMinWindowSize(size);
    DesktopWindow.setMaxWindowSize(size);
  }
  SystemChrome.setPreferredOrientations([DeviceOrientation.portraitUp, DeviceOrientation.portraitDown]);
  runApp(const App());
}

class App extends StatelessWidget {
  const App({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    String title = S().title.toUpperCase();
    return MaterialApp(
      localizationsDelegates: const [GlobalMaterialLocalizations.delegate, S.delegate],
      supportedLocales: S.delegate.supportedLocales,
      title: title,
      debugShowCheckedModeBanner: false,
      theme: ThemeData(primarySwatch: Colors.blue),
      home: MainPage(title: title),
    );
  }
}
