#include "Math.h"

Vector2f SetVector2f(float x, float y) {
    return (Vector2f){x, y};
}

float Normalize(float value, float Max, float Min) {
    return (value - fmin(value, Min)) / (fmax(value, Max) - fmin(value, Min));
}

float Largest(float arr[], int n) {
    int i;
    
    // Initialize maximum element
    float max = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
 
    return max;
}

float Smallest(float arr[], int n) {
    int i;
    
    // Initialize maximum element
    float min = arr[0];
 
    // Traverse array elements from second and
    // compare every element with current max 
    for (i = 1; i < n; i++)
        if (arr[i] < min)
            min = arr[i];
 
    return min;
}