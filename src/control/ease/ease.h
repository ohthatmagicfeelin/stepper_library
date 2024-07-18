#ifndef EASINGCURVES_H
#define EASINGCURVES_H

#include <Arduino.h>
#include <math.h>
#include "functions.h"
#include "../../hardware/stepper/stepper.h"



class Easer {

public:
    Easer(
        EasingType _easeType, 
        Stepper& motor,
        float granularity,
        float duration,
        float stepsToDestination
    );
    
    long actuateEasing();


private:
    struct TimeParameters {
        float duration;
        float granularity;
        float granularityPercent;
        float granularityMicroSeconds;
    };
    struct DisplacementParameters {
        int stepsPerRev;
        float stepsToDestination;
    };

    TimeParameters _tP; 
    DisplacementParameters _dP; 
    EasingType _easeType;
    Stepper& _motor;

    float _calculateEasing(float t, const float stepsToDestination, float duration);
    float _convertTimeToPercent(float currentTime, float totalTime);
    float _convertPercentToSteps(float percentSteps, float totalSteps);
    float _calculateDeltaDisplacement(float tP, const float granularityPrecent);

    float _microsecondsPerStep(float stepsToDisplace, float granularityMicroSeconds);
    float _getGranularityMicroSeconds(float granularity);
    float _getGranularityPercent(float duration, float granularity);
    float _getStepsToDestination(float revolutions, int stepsPerRev);
};
#endif