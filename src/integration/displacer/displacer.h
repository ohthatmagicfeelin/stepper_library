#ifndef DISPLACER_H
#define DISPLACER_H

#include <Arduino.h>
#include "../../hardware/stepper/stepper.h"
// include ese function
#include "../../control/ease/functions.h"
#include "../../control/ease/ease.h"

enum DisplacementType {REVOLUTIONS, STEPS, METRES};

class Displacer {
    
    public:
        Displacer(
            Stepper& motor, 
            float duration, 
            float distance, 
            StepperDirection direction = CLOCKWISE, 
            DisplacementType type = REVOLUTIONS
            
            );
        void actuateDisplacement();

        // --- Setters
        void setGranularity(float granularity);
        void setEaseType(EasingType easeType);
        void setMetresPerRevolution(float metresPerRevolution);

        Stepper& motor;

    private:
        float granularity = 0.01;
        EasingType easeType = PARAMETRIC;

        float duration;
        float distance;
        StepperDirection direction;
        DisplacementType displacementType;

        float metresPerRevolution = 0.06f; // ! This changes with the size of the pulley.

        float _convertRevolutionsToSteps(float revolutions);
        float _convertMetresToSteps(float metres);
        long _convertToSteps(float distance, DisplacementType type);

};


#endif