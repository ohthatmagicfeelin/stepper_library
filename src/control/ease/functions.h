#ifndef EASING_FUNCTIONS_H
#define EASING_FUNCTIONS_H

#include <math.h>

enum EasingCurve {LINEAR, BEZIER, SINUSOIDAL, QUADRATIC, PARAMETRIC, CUBIC, QUARTIC, CIRCULAR};

float applyEasingCurve(EasingCurve easingCurve, float t);

#endif