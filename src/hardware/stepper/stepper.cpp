
#include "stepper.h"

// -------------------------
// ---- Constructor
// -------------------------
Stepper::Stepper(int stepPin, int dirPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin)
    :   _stepPin(stepPin), 
        direction(dirPin), 
        enable(enablePin),
        resolution(ms1Pin, ms2Pin, ms3Pin) {}


void Stepper::begin() {
    pinMode(this->_stepPin, OUTPUT);

    direction.begin();
    direction.setDirection(CLOCKWISE);

    enable.begin();
    enable.setEnable(ENABLE);

    resolution.begin();
    resolution.setResolution(STEP_16);


}


// ---------------------------
// ---- Actuation functions
// ---------------------------

int Stepper::_validateStepPulsePeriod(int stepPulsePeriod) {
    static bool warningPrinted = false;
    if (stepPulsePeriod < this->resolution.getMinPeriod()) {
        if (!warningPrinted) {
            Serial.println(F("Period too small. See 'Min µs Delay' table in stepper.cpp"));
            warningPrinted = true;
        }
        return this->resolution.getMinPeriod();
    }
    return stepPulsePeriod;
}


void Stepper::_step(int delayDuration) {

    digitalWrite(this->_stepPin, HIGH);
    delayMicroseconds(delayDuration);

    digitalWrite(this->_stepPin, LOW);
    delayMicroseconds(delayDuration);
}


void Stepper::step(int stepPulsePeriod) {
    stepPulsePeriod = this->_validateStepPulsePeriod(stepPulsePeriod);

    this->position.trackCurrentPosition(this->direction.getDirection());

    int delayDuration = stepPulsePeriod / 2;
    _step(delayDuration);
}


void Stepper::displaceBySteps(int stepsToDisplace, int stepPeriod) {
    for (long i = 0; i < stepsToDisplace; ++i) {
        this->step(stepPeriod);
    }
}

