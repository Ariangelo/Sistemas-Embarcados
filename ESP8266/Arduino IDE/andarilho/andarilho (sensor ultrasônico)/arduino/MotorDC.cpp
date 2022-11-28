/*
  MotorDC->cpp - Library for flashing MotorDC code->
  Created by Ariangelo Hauer Dias, September 14, 2022->
  Released into the public domain->
*/

#include "MotorDC.h"

MotorDC::MotorDC() {}

MotorDC::MotorDC(String name, int pinVcc, int pinGnd, int pinSpeed) {
  pinMode(pinVcc, OUTPUT);
  pinMode(pinGnd, OUTPUT);
  pinMode(pinSpeed, OUTPUT);

  this->name = name;
  this->pinVcc = pinVcc;
  this->pinGnd = pinGnd;
  this->pinSpeed = pinSpeed;

  setWay(this->way);
  setSpeed(this->speed);
}

String MotorDC::getName() {
  return this->name;
}

void MotorDC::setSpeed(int speed, bool update) {
  if (update) {
    this->speed = speed;
  }
  analogWrite(this->pinSpeed, map(speed, 0, 100, 0, MAX_SPEED_REF));
}

int MotorDC::getSpeed() {
  return this->speed;
}

void MotorDC::setWay(double way) {
  this->way = way;
}

int MotorDC::getWay() {
  return this->way;
}

void MotorDC::run() {
  if (this->way > 0) {
    digitalWrite(this->pinVcc, HIGH);
    digitalWrite(this->pinGnd, LOW);
  } else {
    digitalWrite(this->pinVcc, LOW);
    digitalWrite(this->pinGnd, HIGH);
  }
}