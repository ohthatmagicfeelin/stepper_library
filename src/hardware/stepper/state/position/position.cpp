#include "position.h"

// -------------------------
// ---- Constructor
// -------------------------
PositionTracker::PositionTracker(
    long currentPosition
    )
    :   _currentPosition(currentPosition)
        {}


void PositionTracker::trackCurrentPosition(StepperDirection direction) {
  if (direction == COUNTER_CLOCKWISE) {
    this->_currentPosition--;
  }
  if (direction == CLOCKWISE) {
    this->_currentPosition++;
  }
}

long PositionTracker::getCurrentPosition() {
  return this->_currentPosition;
}

void PositionTracker::resetCurrentPosition() {
  this->_currentPosition = 0;
}

