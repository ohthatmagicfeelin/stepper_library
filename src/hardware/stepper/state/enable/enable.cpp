#include "enable.h"

// -------------------------
// ---- Constructor
// -------------------------
EnableTracker::EnableTracker(int enablePin, StepperEnable enable)
    : _enablePin(enablePin),
      _enable(enable) {}


void EnableTracker::begin() {
    pinMode(this->_enablePin, OUTPUT);
};

void EnableTracker::trackEnable() {}

StepperEnable EnableTracker::getEnable() {
  return this->_enable;
}

void EnableTracker::setEnable(StepperEnable enable) {
    digitalWrite(this->_enablePin, enable == ENABLE ? LOW : HIGH);
    this->_enable = enable;
}

