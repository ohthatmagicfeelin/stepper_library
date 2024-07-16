#include "Stepper.h"


/*
+------+------+------+------------------------+-------------+-------------+-------------+
| MS1  | MS2  | MS3  | Microstep Resolution   | Pulse/Rev   | Min µs Delay| Period (µs) |
+------+------+------+------------------------+-------------+-------------+-------------+
| Low  | Low  | Low  | Full step              | 200         | 530         | 1060        |
| High | Low  | Low  | Half step              | 400         | 250         | 500         |
| Low  | High | Low  | 1/4 step               | 800         | 130         | 260         |
| High | High | Low  | 1/8 step               | 1600        | 70          | 140         |
| High | High | High | 1/16 step              | 3200        | 40          | 80          |
| High | Low  | High | 1/32 step              | 6400        | 31          | 62          |
+------+------+------+------------------------+-------------+-------------+-------------+
*/


const Stepper::ResolutionSetting Stepper::RESOLUTION_SETTINGS[] = {
    {LOW,  LOW,  LOW,  200,  1060,  "Full Step"},
    {HIGH, LOW,  LOW,  400,  500,   "Half Step"},
    {LOW,  HIGH, LOW,  800,  260,   "Quarter Step"},
    {HIGH, HIGH, LOW,  1600, 140,   "Eighth Step"},
    {HIGH, HIGH, HIGH, 3200, 80,    "Sixteenth Step"},
    {HIGH, LOW,  HIGH, 6400, 62,    "Thirty-Second Step"}
};

Stepper::Stepper(int stepPin, int dirPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin)
    :   _stepPin(stepPin), 
        _dirPin(dirPin), 
        _enablePin(enablePin),
        _ms1Pin(ms1Pin), 
        _ms2Pin(ms2Pin), 
        _ms3Pin(ms3Pin),
        _currentResolution(STEP_1), 
        _currentPulsePerRev(RESOLUTION_SETTINGS[STEP_1].pulsePerRev), 
        currentMinPeriod(RESOLUTION_SETTINGS[STEP_1].minPeriod),
        _currentDirection(CLOCKWISE) {}

void Stepper::begin() {
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    pinMode(_ms1Pin, OUTPUT);
    pinMode(_ms2Pin, OUTPUT);
    pinMode(_ms3Pin, OUTPUT);
    setEnable(DISABLE);
    setDirection(CLOCKWISE);
    setResolution(STEP_1);
}

void Stepper::setEnable(StepperEnable state) {
    digitalWrite(_enablePin, state == ENABLE ? LOW : HIGH);
}

int Stepper::setResolution(StepperResolution resolution) {
    const ResolutionSetting& resolutionSettings = RESOLUTION_SETTINGS[resolution];
    digitalWrite(_ms1Pin, resolutionSettings.ms1);
    digitalWrite(_ms2Pin, resolutionSettings.ms2);
    digitalWrite(_ms3Pin, resolutionSettings.ms3);
    _currentResolution = resolution;
    _currentPulsePerRev = resolutionSettings.pulsePerRev;
    currentMinPeriod = resolutionSettings.minPeriod;
}

int Stepper::getPulsePerRev() {
    return _currentPulsePerRev;
}

void Stepper::step(int stepPulsePeriod) {
    if (stepPulsePeriod < currentMinPeriod) {
        stepPulsePeriod == currentMinPeriod;
        Serial.println(F("Period too small. See 'Min µs Delay' table in stepper.cpp"));
    }
    int delayDuration = stepPulsePeriod / 2;
    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(delayDuration);

    digitalWrite(_stepPin, LOW);
    delayMicroseconds(delayDuration);
}

void Stepper::displaceBySteps(int stepsToDisplace, int stepPeriod) {
    for (long i = 0; i < stepsToDisplace; ++i) {
        step(stepPeriod);
    }
}

void Stepper::setDirection(StepperDirection direction) {
    _currentDirection = direction;
    digitalWrite(_dirPin, direction == CLOCKWISE ? HIGH : LOW);
}

StepperDirection Stepper::getDirection() {
    return _currentDirection;
}