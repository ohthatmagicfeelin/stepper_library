// a class with methods that tracker the position of the stepper from a "home" location (home is 0).
// variables include: currentPosition
#ifndef POSITION_TRACKER_H
#define POSITION_TRACKER_H

#include "../../hardware/stepper/stepper.h"

class PositionTracker {

public:
    PositionTracker(
        long currentPosition = 0
    );

    long currentPosition;
    
    void trackCurrentPosition(StepperDirection direction);


private:
};

#endif