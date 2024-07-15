#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

enum StepperEnable { ENABLE, DISABLE };
enum StepperResolution { STEP_1, STEP_2, STEP_4, STEP_8, STEP_16, STEP_32 };
enum StepperDirection { CLOCKWISE, COUNTER_CLOCKWISE };

class Stepper {
public:
    Stepper(int stepPin, int dirPin, int enablePin, int ms1Pin, int ms2Pin, int ms3Pin);
    void begin();
    void setEnable(StepperEnable state);
    int setResolution(StepperResolution resolution);
    void step(int steps, int delayMicros);
    void setDirection(StepperDirection direction);

private:
    int _stepPin;
    int _dirPin;
    int _enablePin;
    int _ms1Pin;
    int _ms2Pin;
    int _ms3Pin;
    int _currentResolution;
    bool _currentDirection;

    struct ResolutionSetting {
        bool ms1;
        bool ms2;
        bool ms3;
        int pulsePerRev;
        const char* name;
    };

    static const ResolutionSetting RESOLUTION_SETTINGS[];
};

#endif