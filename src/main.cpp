


#include <Arduino.h>
#include "hardware/stepper/stepper.h"
#include "hardware/io/io.h"

Stepper motor(
  STEP_PIN,
  DIR_PIN,
  ENABLE_PIN,
  MS1_PIN,
  MS2_PIN,
  MS3_PIN
);

void setup() {
    Serial.begin(9600);
    motor.begin();
}

void loop() {
    motor.setDirection(CLOCKWISE);  
    motor.setEnable(ENABLE);
    // int pulsePerRev = motor.setResolution(STEP_32);
    // motor.step(pulsePerRev, 31);  // Make one full revolution at STEP_32 resolution
    // delay(1000);
    
    motor.setDirection(COUNTER_CLOCKWISE);  // Counter-clockwise
    motor.setResolution(STEP_1);
    motor.step(200, 530);  // Make one full revolution at STEP_1 resolution
    delay(1000);
    while(1) {}
}





