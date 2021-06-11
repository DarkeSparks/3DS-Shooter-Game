#ifndef ROTATED_H
#define ROTATED_H

#include <citro2d.h>
#include "Math.h"

#include "Entity.h"

void DrawRotatedTriangle(Entity e, Vector2f origin, float angle, u32 color);

void DrawLineLA(Vector2f pos, float length, float angle, float thickness);

#endif