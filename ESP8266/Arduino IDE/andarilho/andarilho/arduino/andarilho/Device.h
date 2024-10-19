/*
  Device.h - Library for flashing Device code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef Device_h
#define Device_h

#include "Arduino.h"
#include "MotorDC.h"

#define MAX_NUM_MOTORS 4

enum Turn { LEFT,
            RIGHT };

class Device {
  public:
    Device(String name, uint8_t numMotors, MotorDC motors[]);
    String getName();
    void setSpeed(int speed);
    void setWay(double way);
    void moveOn(double handling[3]);
    void turnBack(Turn dir);

  private:
    String name;
    uint8_t numMotors;
    MotorDC motors[MAX_NUM_MOTORS];
};

#endif
