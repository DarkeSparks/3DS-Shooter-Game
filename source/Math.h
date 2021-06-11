#ifndef MATH_H
#define MATH_H

#include <math.h>

#define DEGTORAD(V) (V * M_PI) / 180
#define RADTODEG(V) (V * 180) / M_PI

#define RANDFLOAT(V) (float)rand() / RAND_MAX * (float)V

typedef struct Vector2f {
    float x, y;
} Vector2f;

Vector2f SetVector2f(float x, float y);

float Normalize(float value, float Max, float Min);

float Largest(float arr[], int n);
float Smallest(float arr[], int n);

#endif