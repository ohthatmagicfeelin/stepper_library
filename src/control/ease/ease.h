#ifndef EASINGCURVES_H
#define EASINGCURVES_H

#include <Arduino.h>
#include <math.h>
#include "functions.h"
#include "../../hardware/stepper/stepper.h"



class Easer {

public:
    Easer(
        EasingCurve _easeType, 
        Stepper motor,
        float granularity,
        float duration,
        float revolutions
    );
    
    long actuateEasing();


private:
    struct TimeParameters {
        float duration;
        float granularity;
        const float granularityPercent;
        const float granularityMicroSeconds;
    };
    struct DisplacementParameters {
        float revolutions;
        float stepsPerRev;
        const float stepsToDestination;
    };

    TimeParameters _tP; 
    DisplacementParameters _dP; 
    EasingCurve _easeType;
    Stepper _motor;

    float _calculateEasing(float t, const float stepsToDestination, float duration);
    float _convertTimeToPercent(float currentTime, float totalTime);
    float _convertPercentToSteps(float percentSteps, float totalSteps);
    float _calculateDeltaDisplacement(float tP, const float granularityPrecent);

    float _microsecondsPerStep(float stepsToDisplace, float granularityMicroSeconds);
    float _getGranularityMicroSeconds(float granularity);
    float _getGranularityPercent(float duration, float granularity);
    float _getStepsToDestination(float revolutions, float stepsPerRev);
};
#endif