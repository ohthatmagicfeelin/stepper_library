
#include "resolution.h"

// -------------------------
// ---- Constructor
// -------------------------
ResolutionTracker::ResolutionTracker(
        int ms1Pin, 
        int ms2Pin, 
        int ms3Pin,
        StepperResolution resolution
)
    :   _ms1Pin(ms1Pin),
        _ms2Pin(ms2Pin),
        _ms3Pin(ms3Pin) {}
    
void ResolutionTracker::begin() {
    pinMode(this->_ms1Pin, OUTPUT);
    pinMode(this->_ms2Pin, OUTPUT);
    pinMode(this->_ms3Pin, OUTPUT);
};
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
/**
 * A table of resolution settings for the A4988 stepper motor driver.
 * Each entry in the table represents a different microstep resolution,
 * with the corresponding MS1, MS2, MS3 pin states, pulses per revolution,
 * minimum pulse period, and a descriptive name.
 */

const ResolutionTracker::ResolutionSettings ResolutionTracker::RESOLUTION_SETTINGS[] = {
    {LOW,  LOW,  LOW,  200,  1060, STEP_1,  "Full Step"},
    {HIGH, LOW,  LOW,  400,  500,  STEP_2,  "Half Step"},
    {LOW,  HIGH, LOW,  800,  260,  STEP_4,  "Quarter Step"},
    {HIGH, HIGH, LOW,  1600, 140,  STEP_8,  "Eighth Step"},
    {HIGH, HIGH, HIGH, 3200, 80,   STEP_16, "Sixteenth Step"},
    {HIGH, LOW,  HIGH, 6400, 62,   STEP_32, "Thirty-Second Step"}
};


void ResolutionTracker::setResolution(StepperResolution resolution) {
    const ResolutionSettings& resolutionSettings = RESOLUTION_SETTINGS[resolution];
    digitalWrite(this->_ms1Pin, resolutionSettings.ms1);
    digitalWrite(this->_ms2Pin, resolutionSettings.ms2);
    digitalWrite(this->_ms3Pin, resolutionSettings.ms3);
    this->_resolutionSettings = resolutionSettings;
}


int ResolutionTracker::getPulsePerRev() {
    return this->_resolutionSettings.pulsePerRev;
}

int ResolutionTracker::getMinPeriod() {
    return this->_resolutionSettings.minPeriod;
}