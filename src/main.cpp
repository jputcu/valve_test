#include "Arduino.h"
#include <Stepper.h>

constexpr int STEPS = 2048; // Reduction 64
constexpr int OPEN_STEPS = 505;
constexpr long MAX_SPEED_RPM = 12;
constexpr long NORMAL_SPEED_RPM = 10;

// Stepper 12VDC
// Connect brown + red -> 12VDC
// 8 -> blue
// 9 -> yellow
// 10 -> pink
// 11 -> orange
Stepper stepper(STEPS, 8, 9, 10, 11);

void homing() {
  stepper.setSpeed(MAX_SPEED_RPM);
  stepper.step(-STEPS/2);
}

void open(int steps = OPEN_STEPS) {
  static int current_step = 0;
  stepper.setSpeed(NORMAL_SPEED_RPM);
  stepper.step(steps - current_step);
  current_step = steps;
}

void setup() {
  homing();
  delay(1000);
  open(OPEN_STEPS/4);
  delay(1000);
  open(OPEN_STEPS/2);
  delay(1000);
  open();

  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
}

void loop() {}
