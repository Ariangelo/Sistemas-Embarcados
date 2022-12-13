#ifndef Config
#define Config

#include <Arduino.h>
#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <Arduino_JSON.h>
#include <Ticker.h>  //para controlar estado do LED
#include <Ultrasonic.h>

#ifdef ESP32
#include <BluetoothSerial.h>
#else
#include <SoftwareSerial.h>
#endif

#if defined(ESP32) && (!defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED))
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

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
bool wifiConnect();
bool mqttConnect(PubSubClient& clienteMQTT, char* server, char* mqttClient, int port, char* mqttTopic);
int connectMQTT(PubSubClient& clienteMQTT);
JSONVar createActions(Source source, String payload);

#endif  // Config