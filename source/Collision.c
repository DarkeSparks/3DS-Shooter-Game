#include "Collision.h"

int LineByLineCollsion(Vector2f pos1, Vector2f pos2, Vector2f pos3, Vector2f pos4) {
    float uA = ((pos4.x-pos3.x)*(pos1.y-pos3.y) - (pos4.y-pos3.y)*(pos1.x-pos3.x)) / ((pos4.y-pos3.y)*(pos2.x-pos1.x) - (pos4.x-pos3.x)*(pos2.y-pos1.y));
    float uB = ((pos2.x-pos1.x)*(pos1.y-pos3.y) - (pos2.y-pos1.y)*(pos1.x-pos3.x)) / ((pos4.y-pos3.y)*(pos2.x-pos1.x) - (pos4.x-pos3.x)*(pos2.y-pos1.y));

    return (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1);
}

int TriangleOnTriangle(Vector2f pos1[3], Vector2f pos2[3]) {
    return (LineByLineCollsion(pos1[0], pos1[1], pos2[0], pos2[1]) ||
            LineByLineCollsion(pos1[0], pos1[1], pos2[1], pos2[2]) || 
            LineByLineCollsion(pos1[0], pos1[1], pos2[2], pos2[0]) || 
            LineByLineCollsion(pos1[1], pos1[2], pos2[0], pos2[1]) ||
            LineByLineCollsion(pos1[1], pos1[2], pos2[1], pos2[2]) || 
            LineByLineCollsion(pos1[1], pos1[2], pos2[2], pos2[0]) || 
            LineByLineCollsion(pos1[2], pos1[0], pos2[0], pos2[1]) ||
            LineByLineCollsion(pos1[2], pos1[0], pos2[1], pos2[2]) || 
            LineByLineCollsion(pos1[2], pos1[0], pos2[2], pos2[0])
        );
}