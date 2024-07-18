#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include "state/position/position.h"
#include "state/direction/direction.h"
#include "state/enable/enable.h"
#include "state/resolution/resolution.h"
#include "state/state.h"


class Stepper {
public:
    Stepper(int stepPin, int dirPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin);

    void begin();

    // --- State tracking objects
    PositionTracker position;
    DirectionTracker direction;
    EnableTracker enable;
    ResolutionTracker resolution;

    // --- Main functions
    void step(int stepPulsePeriod);
    void displaceBySteps(int stepsToDisplace, int stepPeriod);


private:
    int _stepPin;

    void _step(int delayDuration);
    int _validateStepPulsePeriod(int stepPulsePeriod);

};

#endif