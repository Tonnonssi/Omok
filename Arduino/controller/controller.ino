#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "src/Control6DOF.h"

int pins[6] = {0,3,4,7,8,11};
Control6DOF controller(pins);

void setup() {
  Serial.begin(9600);
  Serial.print("Hello World!");

}

void loop() {
  controller.rotateJointsTo(3, {5,4,3}, {30, 60, 90});
  controller.rotateJointsBy(3, {5,4,3}, {10, 10, 10});

}
