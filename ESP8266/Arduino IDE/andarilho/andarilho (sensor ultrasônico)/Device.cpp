/*
  Device.cpp - Library for flashing Device code.
  Created by Ariangelo Hauer Dias, September 14, 2022.
  Released into the public domain.
*/

#include "MotorDC.h"
#include "Device.h"

Device::Device(String name, uint8_t numMotors, MotorDC motors[]) {
  this->name = name;
  this->numMotors = numMotors;
  for (int i = 0; i < this->numMotors; i++) {
    this->motors[i] = motors[i];
  }
}

String Device::getName() {
  return this->name;
}

void Device::setSpeed(int speed) {
  for (int i = 0; i < this->numMotors; i++) {
    this->motors[i].setSpeed(speed);
  }
}

void Device::setWay(double way) {
  for (int i = 0; i < this->numMotors; i++) {
    this->motors[i].setWay(way);
  }
}

void Device::moveOn(double handling[3]) {
  for (int i = 0; i < this->numMotors; i++) {
    if (handling[2] != 0) {
      //this->motors[i].setWay(handling[2]);
      setWay(handling[2]);
    }
    this->motors[i].setSpeed(int(handling[i] * this->motors[i].getSpeed()), false);
    this->motors[i].run();
  }
}

void Device::turnBack(Turn dir) {
  int reducer;
  setWay(-1);
  for (int i = 0; i < this->numMotors; i++) {
    // By avoiding the obstacle, the speed is reduced differently in the motors
    reducer = i == 0
                ? (dir == LEFT ? 2 : 3)
                : (dir == LEFT ? 3 : 2);
    this->motors[i].setSpeed(int(this->motors[i].getSpeed() / reducer), false);
    this->motors[i].run();
  }
  // Wait 4 seconds to perform the action
  delay(4000);
}