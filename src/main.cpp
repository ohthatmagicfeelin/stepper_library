
// TODO: setpoint needs exit condition and pot testing
// TODO: Easing function "period too small" issue needs to be fixed


#include <Arduino.h>
#include "hardware/stepper/stepper.h"
#include "hardware/io/io.h"
#include "integration/displacer/displacer.h"
#include "hardware/stepper/state/state.h"

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
    Displacer displacer(motor, 3, 8, CLOCKWISE, REVOLUTIONS);
    motor.resolution.setResolution(STEP_1);
    displacer.actuateDisplacement();
    while (1) {};
}





