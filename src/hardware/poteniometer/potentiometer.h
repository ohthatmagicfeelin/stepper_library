#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>
// #include "../io/io.h"

class Potentiometer {

public:
    Potentiometer(
        int potPin, 
        int scalePotToRange, // 1023 divided by this number converts pot value to the range given here.
        float binPotIntoResolution // discretisation, granularity, precision of pot readings.
    );
    long getScaledValue();


private:
    int _potPin;
    int _scalePotToRange;
    float _binPotIntoResolution;

    // --- Analog Input Resolution
    // --------------------------------
    static const int ADC_MAX_VALUE = 1023; // For most Arduino boards (10-bit ADC)
    // static const int ADC_MAX_VALUE = 4095; // For ESP32 (12-bit ADC)

    // --- Moving Average Parameters
    // --------------------------------
    static constexpr int MAX_READINGS = 50; // this is needed to initialise "readings" array
    struct MovingAverageParameters {
        int numReadings = MAX_READINGS;
        int readings[MAX_READINGS];
        int readIndex = 0; // Index of the current reading
        long total = 0; // Running total of readings
        int averageReading = 0; // Averaged reading
    };
    MovingAverageParameters mAP;

    void _movingAverageInitialise(long averageInitialise); 
    int _applyMovingAverageFilter(int potReading);
};

#endif