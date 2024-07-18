
#ifndef ENABLE_TRACKER_H
#define ENABLE_TRACKER_H

#include <Arduino.h>
#include "../state.h"

class EnableTracker {

public:
    EnableTracker(
        int enablePin,
        StepperEnable enable = ENABLE
    );

    void begin();

    StepperEnable getEnable();
    void setEnable(StepperEnable enable);
    
    void trackEnable();

private:
    int _enablePin;
    StepperEnable _enable;
};

#endif