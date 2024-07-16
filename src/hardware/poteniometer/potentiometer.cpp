#include "potentiometer.h"

// -------------------------
// ---- Constructor
// -------------------------
Potentiometer::Potentiometer(
    int potPin, 
    int scalePotToRange, 
    float binPotIntoResolution
    )
    :   _potPin(potPin),
        _scalePotToRange(scalePotToRange), 
        _binPotIntoResolution(binPotIntoResolution)
        {
            _movingAverageInitialise(0);
        }



void Potentiometer::_movingAverageInitialise(long averageInitialise) {
    // Initialize all readings to averageInitialise
    for (int i = 0; i < mAP.numReadings; i++) {
        mAP.readings[i] = averageInitialise;
  }
}



int Potentiometer::_applyMovingAverageFilter(int potReading) {
  /* 
    Potentiometer readings are noiisy, causing jittering in motor around setpoint. 
    Moving Average Filterings reduces jitter
    Set "numReadings" to tune the filter.
  */
  mAP.total = mAP.total - mAP.readings[mAP.readIndex]; // Subtract the last reading
  mAP.readings[mAP.readIndex] = potReading; // Add the new reading
  mAP.total = mAP.total + mAP.readings[mAP.readIndex]; // Update the total
  mAP.readIndex = (mAP.readIndex + 1) % mAP.numReadings; // Increment the index and wrap around
  int averageReading = mAP.total / mAP.numReadings; // Calculate the average
  return averageReading;
}


long Potentiometer::getScaledValue() {
    int rawReading = analogRead(_potPin);
    const float conversionFactor = (static_cast<float>(ADC_MAX_VALUE) / _scalePotToRange);
    long scaledValue = round((rawReading / conversionFactor) * _binPotIntoResolution); 
    long filteredValue = _applyMovingAverageFilter(scaledValue);
    return filteredValue;
}
