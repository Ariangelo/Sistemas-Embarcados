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

String payloadBT = "";  // a String to hold incoming data

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
double distance;
unsigned long timeReadDistance = millis();

void setup() {
  Serial.begin(9600);
  Serial.println();
  cabec(Serial);
}

void loop() {
  if (Serial.available()) {
    serialBTevent();
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
