
#ifndef DIRECTION_TRACKER_H
#define DIRECTION_TRACKER_H

#include <Arduino.h>
#include "../state.h"


class DirectionTracker {

public:
    DirectionTracker(
        int dirPin,
        StepperDirection direction = CLOCKWISE
    );

    void begin();

    StepperDirection getDirection();
    void setDirection(StepperDirection direction);
    
    void trackDirection();

private:
    int _dirPin;
    StepperDirection _direction;
};

#endif