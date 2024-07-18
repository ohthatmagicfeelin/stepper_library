
#ifndef RESOLUTION_TRACKER_H
#define RESOLUTION_TRACKER_H

#include <Arduino.h>
#include "../state.h"

class ResolutionTracker {

public:
    ResolutionTracker(
        int ms1Pin, 
        int ms2Pin, 
        int ms3Pin,
        StepperResolution resolution = STEP_16
    );

    void begin();

    int getPulsePerRev();
    int getMinPeriod();

    void setResolution(StepperResolution resolution);

private:
    int _ms1Pin;
    int _ms2Pin;
    int _ms3Pin;
    
    struct ResolutionSettings {
        bool ms1;
        bool ms2;
        bool ms3;
        int pulsePerRev;
        int minPeriod; // ! This may change for other motors. Values obtained by trying smaller delay values until motor stops working.
        StepperResolution resolution;
        const char* name;
    };
    
    ResolutionSettings _resolutionSettings;

    static const ResolutionSettings RESOLUTION_SETTINGS[];
};

#endif