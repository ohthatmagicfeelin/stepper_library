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


void SetpointTracker::_checkIfSetpointSatisfied() {
  if ( (-_setpointError < _setpoint - _positionTrackerInstance.currentPosition) && (_setpoint - _positionTrackerInstance.currentPosition < _setpointError) ) {
    _isSetpointStatisfied = true;
  }
  else {
    _isSetpointStatisfied = false;
  }
}


void SetpointTracker::_updateDirection() {
  if (_setpoint - _positionTrackerInstance.currentPosition > _setpointError) {
    _motorInstance.setDirection(CLOCKWISE);
  }
  else if (_setpoint - _positionTrackerInstance.currentPosition < -_setpointError) {
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


Settings applyAcceleration(Settings settings) {
  if (abs(settings.ctrl.setpoint - settings.ctrl.currentPosition) < 980) {
    settings.ctrl.stepPulsePeriod = settings.ctrl.stepPulsePeriod + 1;
    settings.ctrl.accelerationCounter++;
  }
  else if (settings.ctrl.accelerationCounter == 0) {
    settings.ctrl.stepPulsePeriod = 20;
  }
  else {
    settings.ctrl.accelerationCounter--;
    settings.ctrl.stepPulsePeriod = settings.ctrl.stepPulsePeriod - 1;
  }
  return settings;
}


void SetpointTracker::setpointTracking() {
    

    while(_exitCondition) { // digitalRead(selectButtonPin) == LOW
      _updateSetpointTracking();
      settings.ctrl.stepPulsePeriod = 1000;
      settings.ctrl.accelerationCounter = 980;
      while (!_isSetpointStatisfied) {
        
        settings = applyAcceleration(settings);
        
        _updateSetpointTracking();
        _positionTrackerInstance.trackCurrentPosition();
        _motorInstance.step(_stepPulsePeriod);
      }

    }
    delay(300); // debounce delay

}
