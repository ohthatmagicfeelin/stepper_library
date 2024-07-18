// #include "sequence.h"


// Sequence::Sequence(Stepper motor ,SequenceType type) 
// : motor(motor),
//   _type(type) {}



// StepperDirection setDirectionType(bool isDeltaDirectionPositive) {
//   StepperDirection direction;
//   if (isDeltaDirectionPositive) {
//     direction = CLOCKWISE;
//   }
//   else {
//     direction = COUNTER_CLOCKWISE;
//   }
//   return direction;
// }

// Settings updateCurrentPosition(Settings settings, long stepCount, bool isDeltaDirectionPositive) {
//   if (isDeltaDirectionPositive) { 
//     settings.ctrl.currentPosition += stepCount;
//   }
//   else {
//     settings.ctrl.currentPosition -= stepCount;
//   }
//   return settings;
// }


// // Sequence::goToPosition() {
// //   StepperDirection direction;
// //   float revolutions = abs(static_cast<float>(deltaSteps) / stepsPerRevolution);
// //   bool isDeltaDirectionPositive = deltaSteps > 0L;

// //   direction = setDirectionType(deltaSteps);

// //   long stepCount = actuateEasing(direction, settings.duration, revolutions, settings.easeType, settings.granularity);
  
// //   settings = updateCurrentPosition(settings, stepCount, isDeltaDirectionPositive);
// //   return settings;
// // }


// void Sequence::goToPosition() {

//   if (_type == HOME) {
//     Displacer displacer(motor, 3, 15, COUNTER_CLOCKWISE, REVOLUTIONS);
//     displacer.actuateDisplacement();

//     motor.enable.setEnable(ENABLE);  // re-enable stepper after limit switch hit.
//     // detachLimitInterrupts(); // Turn off interrupts momentarily

//     Displacer displacer(motor, 1, 0.2, CLOCKWISE, REVOLUTIONS);
//     displacer.actuateDisplacement(); // Move away from limit

//     displacer.motor.position.resetCurrentPosition(); // set HOME position to step position 0.

//     // attachLimitInterrupts(); // Turn interrupts back on.
//     motor.enable.setEnable(ENABLE); // !! This seems to be needed after limit switch is reattached?? Not sure why.
//   }

//   if (_type == START) {
//     long deltaSteps = startPosition - currentPosition;
//     Displacer displacer(motor, duration, deltaSteps, COUNTER_CLOCKWISE, STEPS).actuateDisplacement();
//   }

//   if (_type == END) {
//     long deltaSteps = endPosition - currentPosition;
//     Displacer displacer(motor, duration, deltaSteps, CLOCKWISE, STEPS);
//     displacer.actuateDisplacement();
//     return settings;
//   }
// }