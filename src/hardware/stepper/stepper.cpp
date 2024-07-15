#include "Stepper.h"

const Stepper::ResolutionSetting Stepper::RESOLUTION_SETTINGS[] = {
    {LOW,  LOW,  LOW,  200,  "Full Step"},
    {HIGH, LOW,  LOW,  400,  "Half Step"},
    {LOW,  HIGH, LOW,  800,  "Quarter Step"},
    {HIGH, HIGH, LOW,  1600, "Eighth Step"},
    {HIGH, HIGH, HIGH, 3200, "Sixteenth Step"},
    {HIGH, LOW,  HIGH, 6400, "Thirty-Second Step"}
};

Stepper::Stepper(int stepPin, int dirPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin)
    : _stepPin(stepPin), _dirPin(dirPin), _enablePin(enablePin),
      _ms1Pin(ms1Pin), _ms2Pin(ms2Pin), _ms3Pin(ms3Pin),
      _currentResolution(STEP_1), _currentDirection(CLOCKWISE) {}

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
    const ResolutionSetting& setting = RESOLUTION_SETTINGS[resolution];
    digitalWrite(_ms1Pin, setting.ms1);
    digitalWrite(_ms2Pin, setting.ms2);
    digitalWrite(_ms3Pin, setting.ms3);
    _currentResolution = resolution;
    return setting.pulsePerRev;
}

void Stepper::step(int steps, int delayMicros) {
    for (int i = 0; i < steps; ++i) {
        digitalWrite(_stepPin, HIGH);
        delayMicroseconds(delayMicros);
        digitalWrite(_stepPin, LOW);
        delayMicroseconds(delayMicros);
    }
}

void Stepper::setDirection(StepperDirection direction) {
    _currentDirection = direction;
    digitalWrite(_dirPin, direction == CLOCKWISE ? HIGH : LOW);
}