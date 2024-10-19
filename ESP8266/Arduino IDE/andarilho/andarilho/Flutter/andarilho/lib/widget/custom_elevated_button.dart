import 'package:flutter/material.dart';

// ignore: must_be_immutable
class CustomElevatedButton extends StatelessWidget {
  EdgeInsetsGeometry? padding;
  String label;
  Widget icon;
  Color? color;
  double? height;
  double? width;
  VoidCallback? onPressed;

  CustomElevatedButton(
      {super.key,
      this.padding,
      required this.label,
      required this.icon,
      this.height = 0.0,
      this.width = 0.0,
      this.color,
      this.onPressed});

  @override
  Widget build(BuildContext context) {
    return Container(
        padding: padding,
        width: width != 0.0 ? width : null,
        child: ElevatedButton.icon(
          label: Text(label),
          icon: icon,
          style: ElevatedButton.styleFrom(
              elevation: 5,
              backgroundColor: color,
              padding: const EdgeInsets.all(15)),
          onPressed: onPressed,
        ));
  }
}
