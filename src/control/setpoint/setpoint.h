#ifndef SETPOINT_H
#define SETPOINT_H

#include <Arduino.h>
#include "../../hardware/stepper/stepper.h"
#include "../../hardware/stepper/state/position/position.h"

// TODO: Add exit condition and getSetpoint function.

class SetpointTracker {

public:
    SetpointTracker(
        long setpoint,
        Stepper motor,
        bool (*exitCondition)(), // keep tracking setpoint until exit condition is true
        long (*getSetpoint)() // function to calculate setpoint, eg. reading a potentiometer.
    );

    void setpointTracking();


private:

    // --- Setpoint Parameter
    long _setpoint;
    bool _isSetpointStatisfied;
    const int _setpointTolerance = 50; // in steps. Reduces the sensitivity of the relay controller.

    // --- Class instances
    Stepper motor;

    // --- Acceleration/Velocity Parameters
    int _minStepPeriod = motor.resolution.getMinPeriod() * 1.5;
    int _maxStepPeriod = motor.resolution.getMinPeriod() * 5;
    int _stepPulsePeriod = _maxStepPeriod; // start at slowest, ramp up to fastest.
    int _accelerationCounter = _maxStepPeriod - _minStepPeriod;

    // --- Function Pointers
    bool (*_exitCondition)();
    long (*_getSetpoint)();

    // --- Internal methods
    void _checkIfSetpointSatisfied();
    long _calculatePositionError();
    void _updateDirection();
    void _updateRelayController();
    void _updateSetpointTracking();
    void _applyAcceleration();
};

#endif