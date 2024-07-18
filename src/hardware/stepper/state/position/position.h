// a class with methods that tracker the position of the stepper from a "home" location (home is 0).
// variables include: currentPosition
#ifndef POSITION_TRACKER_H
#define POSITION_TRACKER_H

#include "../state.h"

class PositionTracker {

public:
    PositionTracker(
        long currentPosition = 0
    );

    
    void trackCurrentPosition(StepperDirection direction);

    long getCurrentPosition();
    void resetCurrentPosition();

private:
    long _currentPosition;
};

#endif