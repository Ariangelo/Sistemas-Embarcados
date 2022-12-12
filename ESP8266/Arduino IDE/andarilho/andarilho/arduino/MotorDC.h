/*
  MotorDC.h - Library for flashing MotorDC code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef MotorDC_h
#define MotorDC_h

#include "Arduino.h"

#define MAX_SPEED_REF 350

class MotorDC {
  public:
    MotorDC();
    MotorDC(String name, int pinVcc, int pinGnd, int pinSpeed);
    String getName();
    void setSpeed(int speed, bool update = true);
    int getSpeed();
    void setWay(double way);
    int getWay();
    void run();

  private:
    String name;
    int speed = 30;
    int way = 1;
    int pinVcc;
    int pinGnd;
    int pinSpeed;
};

#endif
