#include "functions.h"

// -------------------------
// ---- Curve Deinitions
// -------------------------

float linear(float t) {
    return t;
}


float bezier(float t) {
    return t * t * (3.0f - 2.0f * t);
}


float sinusoidal(float t) {
    return -(cos(M_PI * t) - 1) / 2;
}


float quadratic(float t) {
    if (t <= 0.5f) {
        return 2.0f * t * t;
    }
    if (t > 0.5f) {
        return 2.0f * (1.0f - t) * (1.0f - t) + 1.0f;
    }
    return -1;
}


float parametric(float t) {
    float sqr = t * t;
    return sqr / (2.0f * (sqr - t) + 1.0f);
}


float cubic(float t) {
    if(t <= 0.5f) {
        return 4.0f * t * t * t;
    }  
    if(t > 0.5f) {
        return -4.0f * (1.0f-t) * (1.0f-t) * (1.0f-t) + 1.0f;
    }  
    return -1;
}


float quartic(float t) {
    if(t <= 0.5f) {
        return 8.0f * t * t * t * t;
    }  
    if(t > 0.5f) {
        return -8.0f * (1.0f-t) * (1.0f-t) * (1.0f-t) * (1.0f-t) + 1.0f;
    }  
    return -1;
}


float circular(float t) {
    if(t <= 0.5f) {
        return -(sqrt(0.25-t*t)-0.5);
    }  
    if(t > 0.5f) {
        return sqrt(0.25 - (t-1) * (t-1)) + 0.5;
    }  
    return -1;
}




// --------------------------------
// ---- Dispatcher/Wrapper Function
// --------------------------------
float applyEasingCurve(EasingCurve easingCurve, float t) {
    switch (easingCurve) {
        case LINEAR:
            return linear(t);
        case BEZIER:
            return bezier(t);
        case SINUSOIDAL:
            return sinusoidal(t);
        case QUADRATIC:
            return quadratic(t);
        case PARAMETRIC:
            return parametric(t);
        case CUBIC:
            return cubic(t);
        case QUARTIC:
            return quartic(t);
        case CIRCULAR:
            return circular(t);
        default:
            return t; // Return input value as fallback
    }
}

