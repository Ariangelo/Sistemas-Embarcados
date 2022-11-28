#ifndef Config
#define Config

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <Ultrasonic.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 22  // ESP32 DOES NOT DEFINE LED_BUILTIN
#endif

#define BT_NAME "Andarilho"
#define NUM_MOTORS 2

#define PWM_A 14
#define PWM_B 0
#define AI1 13
#define AI2 12
#define BI1 5
#define BI2 4
#define TRIGGER_PIN 2
#define ECHO_PIN 15

enum Source {
  BT,
  MQTT
};

extern JSONVar actions;
bool cabec(Stream& port);

JSONVar createActions(Source source, String payload);

#endif  // Config