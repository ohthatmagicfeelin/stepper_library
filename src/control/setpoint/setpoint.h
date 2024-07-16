#ifndef SETPOINT_H
#define SETPOINT_H

#include <Arduino.h>
#include "../../hardware/stepper/stepper.h"
#include "../position/tracker.h"

// TODO: Add exit condition and getSetpoint function.

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

    const int _setpointTolerance = 50; // in steps. Reduces the sensitivity of the relay controller.
    bool _isSetpointStatisfied;
    
    int _minStepPeriod = _motorInstance.currentMinPeriod * 1.5;
    int _maxStepPeriod = _motorInstance.currentMinPeriod * 5;
    int _stepPulsePeriod = _maxStepPeriod; // start at slowest, ramp up to fastest.
    int _accelerationCounter = _maxStepPeriod - _minStepPeriod;

    // --- Function Pointers
    bool (*_exitCondition)();
    long (*_getSetpoint)();

    void _checkIfSetpointSatisfied();
    long _calculatePositionError();
    void _updateDirection();
    void _updateRelayController();
    void _updateSetpointTracking();
    void _applyAcceleration();
    void setpointTracking();
};
// Settings setpointTracking(Settings settings, long setpointInitialise);

#endif