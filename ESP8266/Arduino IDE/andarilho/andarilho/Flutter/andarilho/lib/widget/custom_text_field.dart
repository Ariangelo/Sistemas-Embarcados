import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

class CustomTextField extends StatelessWidget {
  double padding;
  bool? isDense;
  EdgeInsetsGeometry? contentPadding;
  String? labelText;
  String? hintText;
  String helperText;
  String counterText;
  Widget? counter;
  bool autofocus;
  bool readOnly;
  bool enabled;
  int? maxLength;
  TextStyle? style;
  int maxLines;
  TextCapitalization textCapitalization;
  TextInputType? keyboardType;
  List<TextInputFormatter>? inputFormatters;
  String obscuringCharacter;
  bool obscureText;
  Widget? prefixIcon;
  Widget? suffixIcon;
  bool border;
  FormFieldValidator<String>? validator;
  ValueChanged<String>? onChanged;
  FormFieldSetter<String>? onSaved;
  TextEditingController? controller;
  FocusNode? focusNode;

  CustomTextField(
      {super.key, this.padding = 0.0,
      this.contentPadding,
      this.isDense = false,
      this.labelText,
      this.controller,
      this.focusNode,
      this.enabled = true,
      this.maxLength,
      this.style,
      this.textCapitalization = TextCapitalization.none,
      this.keyboardType,
      this.inputFormatters,
      this.hintText,
      this.helperText = '',
      this.counterText = '',
      this.counter,
      this.autofocus = false,
      this.readOnly = false,
      this.maxLines = 1,
      this.obscuringCharacter = '*',
      this.obscureText = false,
      this.prefixIcon,
      this.suffixIcon,
      this.border = true,
      this.validator,
      this.onChanged,
      this.onSaved});

  @override
  Widget build(BuildContext context) {
    return Container(
      padding: EdgeInsets.symmetric(
        vertical: 8,
        horizontal: padding,
      ),
      child: TextFormField(
        decoration: InputDecoration(
          labelText: labelText,
          isDense: isDense,
          contentPadding: contentPadding,
          floatingLabelBehavior: FloatingLabelBehavior.always,
          hintText: hintText,
          helperText: helperText,
          counterText: counterText,
          counter: counter,
          border: border ? const OutlineInputBorder() : const UnderlineInputBorder(),
          prefixIcon: prefixIcon,
          suffixIcon: suffixIcon,
        ),
        textAlign: TextAlign.justify,
        textCapitalization: textCapitalization,
        keyboardType: keyboardType,
        maxLength: maxLength,
        inputFormatters: inputFormatters,
        style: style,
        maxLines: maxLines,
        obscuringCharacter: obscuringCharacter,
        obscureText: obscureText,
        autofocus: autofocus,
        readOnly: readOnly,
        enabled: enabled,
        controller: controller,
        focusNode: focusNode,
        validator: validator,
        onChanged: onChanged,
        onSaved: onSaved,
      ),
    );
  }
}
