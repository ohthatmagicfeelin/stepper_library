#ifndef EASING_FUNCTIONS_H
#define EASING_FUNCTIONS_H

#include <math.h>

enum EasingType {LINEAR, BEZIER, SINUSOIDAL, QUADRATIC, PARAMETRIC, CUBIC, QUARTIC, CIRCULAR};

float applyEasingCurve(EasingType easingType, float t);

#endif