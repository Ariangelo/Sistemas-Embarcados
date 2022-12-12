import 'package:andarilho/screens/main_page/main_page.dart';
import 'package:andarilho/utility/process_speech_command.dart';
import 'package:flutter/material.dart' hide Ink;
import 'package:google_mlkit_digital_ink_recognition/google_mlkit_digital_ink_recognition.dart';

class DigitalInkPage extends StatefulWidget {
  final MainPage mainPage;
  DigitalInkPage({Key? key, required this.mainPage}) : super(key: key);

  DigitalInkPageState digitalInkPageState = DigitalInkPageState();

  @override
  DigitalInkPageState createState() => digitalInkPageState;
}

class DigitalInkPageState extends State<DigitalInkPage> {
  @override
  Widget build(BuildContext context) {
    return Expanded(
        child: Container(
            margin: const EdgeInsets.symmetric(vertical: 5, horizontal: 10),
            padding: const EdgeInsets.symmetric(vertical: 5, horizontal: 10),
            decoration: BoxDecoration(border: Border.all(), borderRadius: const BorderRadius.all(Radius.circular(10))),
            child: DigitalInkView(mainPage: widget.mainPage)));
  }
}

class DigitalInkView extends StatefulWidget {
  final MainPage mainPage;
  DigitalInkView({Key? key, required this.mainPage}) : super(key: key);

  @override
  _DigitalInkViewState createState() => _DigitalInkViewState();
}

class _DigitalInkViewState extends State<DigitalInkView> {
  final ProcessSpeechCommand processSpeechCommand = ProcessSpeechCommand();
  final DigitalInkRecognizerModelManager modelManager = DigitalInkRecognizerModelManager();
  final String language = 'pt-BR';
  late final DigitalInkRecognizer digitalInkRecognizer = DigitalInkRecognizer(languageCode: language);
  final Ink ink = Ink();
  List<StrokePoint> points = [];
  String recognizedText = '';

  @override
  void initState() {
    super.initState();
    modelManager.isModelDownloaded(language).then(
          (value) => !value
              ? modelManager.downloadModel(language).then((value) => value ? 'success' : 'failed')
              : print('not downloaded'),
        );
  }

  @override
  void dispose() {
    digitalInkRecognizer.close();
    super.dispose();
  }

  void clearPad() {
    setState(() {
      ink.strokes.clear();
      points.clear();
      recognizedText = '';
    });
  }

  Future<void> recogniseText() async {
    try {
      final candidates = await digitalInkRecognizer.recognize(ink);
      recognizedText = candidates.first.text;
      widget.mainPage.controlPage.setAction(processSpeechCommand.sendCommand(
          widget.mainPage.controlPage.currentSpeedValue,
          '${processSpeechCommand.device['name'][0]} ${recognizedText.toLowerCase()}'));
      setState(() {});
      Future.delayed(const Duration(seconds: 3), () {
        clearPad();
      });
    } catch (e) {
      Future.delayed(const Duration(seconds: 2), () {
        clearPad();
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      crossAxisAlignment: CrossAxisAlignment.center,
      children: [
        Expanded(
            child: GestureDetector(
          onPanStart: (DragStartDetails details) {
            ink.strokes.add(Stroke());
          },
          onPanUpdate: (DragUpdateDetails details) {
            setState(() {
              final RenderObject? object = context.findRenderObject();
              final localPosition = (object as RenderBox?)?.globalToLocal(details.globalPosition);
              if (localPosition != null) {
                points = List.from(points)
                  ..add(StrokePoint(
                    x: localPosition.dx,
                    y: localPosition.dy,
                    t: DateTime.now().millisecondsSinceEpoch,
                  ));
              }
              if (ink.strokes.isNotEmpty) {
                ink.strokes.last.points = points.toList();
              }
            });
          },
          onPanEnd: (DragEndDetails details) {
            points.clear();
            setState(() {});
          },
          child: CustomPaint(
            painter: Signature(ink: ink),
            size: Size.infinite,
          ),
        )),
        recognizedText.isNotEmpty
            ? Text(
                recognizedText,
                style: TextStyle(fontSize: 23),
              )
            : Visibility(
                visible: ink.strokes.isEmpty,
                child: Text(
                  'ESCREVA O COMANDO DESEJADO',
                  style: TextStyle(fontSize: 23),
                )),
        Visibility(
            visible: ink.strokes.isNotEmpty,
            child: FloatingActionButton(
              onPressed: recogniseText,
              child: const Icon(Icons.gesture),
            )),
      ],
    );
  }
}

class Signature extends CustomPainter {
  Ink ink;

  Signature({required this.ink});

  @override
  void paint(Canvas canvas, Size size) {
    final Paint paint = Paint()
      ..color = Colors.blue
      ..strokeCap = StrokeCap.round
      ..strokeWidth = 4.0;

    for (final stroke in ink.strokes) {
      for (int i = 0; i < stroke.points.length - 1; i++) {
        final p1 = stroke.points[i];
        final p2 = stroke.points[i + 1];
        canvas.drawLine(Offset(p1.x.toDouble(), p1.y.toDouble()), Offset(p2.x.toDouble(), p2.y.toDouble()), paint);
      }
    }
  }

  @override
  bool shouldRepaint(Signature oldDelegate) => true;
}
