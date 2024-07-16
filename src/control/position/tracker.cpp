#include "tracker.h"

// -------------------------
// ---- Constructor
// -------------------------
PositionTracker::PositionTracker(
    long currentPosition
    )
    :   currentPosition(currentPosition)
        {}


void PositionTracker::trackCurrentPosition(StepperDirection direction) {
  if (direction == COUNTER_CLOCKWISE) {
    currentPosition--;
  }
  if (direction == CLOCKWISE) {
    currentPosition++;
  }
}
