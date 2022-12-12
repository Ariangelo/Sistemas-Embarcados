#include "Config.h"
#include "MotorDC.h"
#include "Device.h"

MotorDC leftMotor = MotorDC("Motor Esquerdo", AI1, AI2, PWM_A);
MotorDC rightMotor = MotorDC("Motor Direito", BI1, BI2, PWM_B);
MotorDC motors[NUM_MOTORS] = { leftMotor, rightMotor };
Device andarilho = Device(BT_NAME, NUM_MOTORS, motors);
double listActions[9][3] = {
  { 1.0, 1.0, 1 }, { 0.0, 1.0, 0 }, { 0.0, 0.0, 0 }, { 1.0, 0.0, 0 }, { 1.0, 1.0, -1 }, { 0.5, 1.0, 1 }, { 1.0, 0.5, 1 }, { 0.7, 1.0, -1 }, { 1.0, 0.7, -1 }
};
JSONVar actions;
int oldAction = 0, oldSpeed = 0;

bool wifiConnected = false;
WiFiClient wifiClient;
PubSubClient clienteMQTT(wifiClient);
char* mqttServer = "broker.mqtt-dashboard.com";
char* mqttIdClient = "arduino-robo-Ariangelo";
char* mqttTopic = "embarcados.controle.robo.payload";
int mqttPort = 1883;
int tryConnectMQTT = 0;

String payloadBT = "";  // a String to hold incoming data

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
double distance;
unsigned long timeReadDistance = millis();

void setup() {
  Serial.begin(9600);
  Serial.println();
  cabec(Serial);
  wifiConnected = wifiConnect();
  if (wifiConnected) {
    mqttConnect(clienteMQTT, mqttServer, mqttIdClient, mqttPort, mqttTopic);
  } else {
    Serial.println("Não foi possível conectar na rede WiFi");
  }
}

void loop() {
  if (Serial.available()) {
    serialBTevent();
  }

  if (wifiConnected) {
    if (tryConnectMQTT <= 2) {
      if (!clienteMQTT.connected() ) {
        tryConnectMQTT += connectMQTT(clienteMQTT) == 1 ? 1 : 100;
      } else {
        clienteMQTT.loop();
      }
    }
  }

  if (millis() - timeReadDistance > 1000) {
    // Read the value returned by the distance sensor
    distance = ultrasonic.read();
    timeReadDistance = millis();
  }

  // If any obstacles are detected, it determines the maneuver time,
  // in the case 4 seconds
  if (distance <= 20) {
    andarilho.turnBack(LEFT);
  } else {
    oldAction = 0;
  }

  if ((int)actions["speed"] != oldSpeed) {
    andarilho.setSpeed((int)actions["speed"]);
    oldSpeed = (int)actions["speed"];
  }

  if ((int)actions["action"] != oldAction) {
    andarilho.moveOn(listActions[(int)actions["action"] - 1]);
    oldAction = (int)actions["action"];
  }
}

void serialBTevent() {
  while (Serial.available()) {
    char payload = (char)Serial.read();
    payloadBT += payload;
    if (payload == '\n') {
      payloadBT.trim();
      actions = createActions(BT, payloadBT);
      payloadBT = "";
    }
  }
}
