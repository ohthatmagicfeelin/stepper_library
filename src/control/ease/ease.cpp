#include "ease.h"

// -------------------------
// ---- Constructor
// -------------------------
Easer::Easer(
    EasingCurve easeType, 
    Stepper motor, 
    float granularity, 
    float duration, 
    float revolutions
    )
    :   _easeType(easeType),
        _motor(motor),
        _dP{
            revolutions,
            _motor.getPulsePerRev(),
            _getStepsToDestination(revolutions, _motor.getPulsePerRev())
        },
        _tP{
            duration, 
            granularity, 
            _getGranularityPercent(duration, granularity),
            _getGranularityMicroSeconds(granularity)
            }
        {}



// -------------------------
// ---- Utility Functions
// -------------------------
float Easer::_convertTimeToPercent(float currentTime, float totalTime) {
    return currentTime / totalTime;
}


float Easer::_convertPercentToSteps(float percentSteps, float stepsToDestination) {
    return round(percentSteps * stepsToDestination);
}


float Easer::_microsecondsPerStep(float stepsToDisplace, float granularityMicroSeconds) {
  return round(granularityMicroSeconds / stepsToDisplace);
}


float Easer::_getGranularityMicroSeconds(float granularity) {
    return granularity * 1000L * 1000L;
}


float Easer::_getGranularityPercent(float duration, float granularity) {
    return granularity / duration;
}


float Easer::_getStepsToDestination(float revolutions, float stepsPerRev) {
    return  stepsPerRev * revolutions;
}



// -------------------------
// ---- Easing Calculation
// -------------------------
float Easer::_calculateDeltaDisplacement(float tPercent, const float granularityPrecent) {
    float deltaT = tPercent - granularityPrecent;
    float currentDisplacePercent = easingFunction(_easeType, tPercent); 
    float previousDisplacePercent = easingFunction(_easeType, constrain(deltaT, 0.0f, 1000.0f)); // no maximum constraint 
    float deltaD = currentDisplacePercent - previousDisplacePercent;
    return deltaD;
}


float Easer::_calculateEasing(float t, const float stepsToDestination, float duration) {
    float tPercent = _convertTimeToPercent(t, duration);
    float deltaD = _calculateDeltaDisplacement(tPercent, _tP.granularityPercent);
    float steps = _convertPercentToSteps(deltaD, stepsToDestination); 
    return steps;
}


long Easer::actuateEasing() {
    float stepsToDisplace = 0;
    float t = 0.0;
    long stepCount = 0;

    while (t < _tP.duration) {
        stepsToDisplace = _calculateEasing(t, _dP.stepsToDestination, _tP.duration);
        long stepPeriod = _microsecondsPerStep(stepsToDisplace, _tP.granularityMicroSeconds);
        t += _tP.granularity;
        stepCount += stepsToDisplace;
        _motor.displaceBySteps(stepsToDisplace, stepPeriod);
    }
    return stepCount;
}

