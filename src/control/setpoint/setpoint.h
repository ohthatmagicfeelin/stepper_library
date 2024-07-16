#ifndef SETPOINT_H
#define SETPOINT_H

#include <Arduino.h>
#include "../../hardware/stepper/stepper.h"
#include "../position/tracker.h"

class SetpointTracker {

public:
    SetpointTracker(
        long setpoint,
        Stepper motor,
        bool (*exitCondition)(), // keep tracking setpoint until exit condition is true
        long (*getSetpoint)(), // function to calculate setpoint, eg. reading a potentiometer.
        int stepPulsePeriod
    );


private:
    long _setpoint;

    PositionTracker _positionTrackerInstance; // intialises currentPosition to 0.
    Stepper _motorInstance;

    const int _setpointError = 50; // in steps
    bool _isSetpointStatisfied;
    int _stepPulsePeriod = _motorInstance.currentMinPeriod;

    // --- Function Pointers
    bool (*_exitCondition)();
    long (*_getSetpoint)();

    void _checkIfSetpointSatisfied();
    void _updateDirection();
    void _updateRelayController();
    void _updateSetpointTracking();
    void setpointTracking();
};
// Settings setpointTracking(Settings settings, long setpointInitialise);

#endif