// setpoint.cpp
#include "setpoint.h"

SetpointTracker::SetpointTracker(
    long setpoint,
    Stepper motor,
    bool (*exitCondition)(), // keep tracking setpoint until exit condition is true
    long (*getSetpoint)(), // function to calculate setpoint, eg. reading a potentiometer.
    int stepPulsePeriod
    )
    :   _setpoint(setpoint),
        _motorInstance(motor),
        _exitCondition(exitCondition),
        _getSetpoint(getSetpoint),
        _stepPulsePeriod(stepPulsePeriod)
        {}

long SetpointTracker::_calculatePositionError() {
    return _setpoint - _positionTrackerInstance.currentPosition;
}

void SetpointTracker::_checkIfSetpointSatisfied() {
  if ( (-_setpointTolerance < _calculatePositionError()) && (_calculatePositionError() < _setpointTolerance) ) {
    _isSetpointStatisfied = true;
  }
  else {
    _isSetpointStatisfied = false;
  }
}


void SetpointTracker::_updateDirection() {
  if (_calculatePositionError() > _setpointTolerance) {
    _motorInstance.setDirection(CLOCKWISE);
  }
  else if (_calculatePositionError() < -_setpointTolerance) {
    _motorInstance.setDirection(COUNTER_CLOCKWISE);
  }
}


void SetpointTracker::_updateRelayController() {
  _checkIfSetpointSatisfied();
  if (!_isSetpointStatisfied) {
    _updateDirection();
  }
}


void SetpointTracker::_updateSetpointTracking() {
  _setpoint = _getSetpoint();
  _updateRelayController();
}


void SetpointTracker::_applyAcceleration() {
  /* Linear acceleration and deceleration for first and last part of motor movement
     Constant velocity for middle part of motor movement.
     */

  if (abs(_calculatePositionError()) < _maxStepPeriod) {
    _stepPulsePeriod = _stepPulsePeriod + 1;
    _accelerationCounter++;
  }
  else if (_accelerationCounter == 0) {
    _stepPulsePeriod = _minStepPeriod;
  }
  else {
    _stepPulsePeriod = _stepPulsePeriod - 1;
    _accelerationCounter--;
  }
}


void SetpointTracker::setpointTracking() {
    
    while(_exitCondition) { // digitalRead(selectButtonPin) == LOW
      _updateSetpointTracking();

      while (!_isSetpointStatisfied) {
        _applyAcceleration();
        _updateSetpointTracking();

        _positionTrackerInstance.trackCurrentPosition(_motorInstance.getDirection());
        _motorInstance.step(_stepPulsePeriod);
      }

    }
    delay(300); // debounce delay

}
