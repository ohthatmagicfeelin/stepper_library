#include "displacer.h"


Displacer::Displacer(Stepper& motor, float duration, float distance, StepperDirection direction, DisplacementType type) 
:   motor(motor),
    duration(duration),
    distance(distance), 
    direction(direction),
    displacementType(type)
    {}

// ---------------------------
// ---- Setters
// ---------------------------
void Displacer::setMetresPerRevolution(float metresPerRevolution) {
    this->metresPerRevolution = metresPerRevolution;
}

void Displacer::setGranularity(float granularity) {
    this->granularity = granularity;
}

void Displacer::setEaseType(EasingType easeType) {
    this->easeType = easeType;
}


float Displacer::_convertMetresToSteps(float metres) {
    float revolutions = metres / this->metresPerRevolution;
    return _convertRevolutionsToSteps(revolutions);
}

float Displacer::_convertRevolutionsToSteps(float revolutions) {
    return static_cast<float>(this->motor.resolution.getPulsePerRev()) * revolutions;
}

long Displacer::_convertToSteps(float distance, DisplacementType type) {
    switch (type) {
        case STEPS:
            return static_cast<long>(distance);  // distance already in steps
        case REVOLUTIONS:
            return _convertRevolutionsToSteps(distance);
        case METRES:
            return _convertMetresToSteps(distance);
        default:
            return 0;  // Or handle error case as appropriate
    }
}



void Displacer::actuateDisplacement() {

    this->distance = _convertToSteps(this->distance, this->displacementType);
    this->motor.direction.setDirection(this->direction);

    Easer easer(
        this->easeType,           // Easing Function
        this->motor,              // Motor Instance
        this->granularity,        // Granularity
        this->duration,           // Duration
        this->distance            // steps
    );

    easer.actuateEasing();
