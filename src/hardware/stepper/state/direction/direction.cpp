#include "direction.h"

// -------------------------
// ---- Constructor
// -------------------------
DirectionTracker::DirectionTracker(int dirPin, StepperDirection direction)
    :   _dirPin(dirPin),   
        _direction(direction) {}

void DirectionTracker::begin() {
    pinMode(this->_dirPin, OUTPUT);
};


void DirectionTracker::trackDirection() {}


StepperDirection DirectionTracker::getDirection() {
  return this->_direction;
}

void DirectionTracker::setDirection(StepperDirection direction) {
    this->_direction = direction;
}

