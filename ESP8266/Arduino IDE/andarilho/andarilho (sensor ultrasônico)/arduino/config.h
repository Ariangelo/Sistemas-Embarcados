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

#define PWM_A 14      // D5
#define PWM_B 0       // D3
#define AI1 13        // D7
#define AI2 12        // D6
#define BI1 5         // D1
#define BI2 4         // D2
#define TRIGGER_PIN 2 // D4
#define ECHO_PIN 15   // D8

enum Source {
  BT,
  MQTT
};

extern JSONVar actions;
bool cabec(Stream& port);

JSONVar createActions(Source source, String payload);

#endif  // Config