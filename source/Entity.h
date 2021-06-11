#ifndef ENTITY_H
#define ENTITY_H

#include "Math.h"
#include "Collision.h"
#include <citro2d.h>

typedef struct Entity {
    Vector2f pos[3];

    float angle;

    u32 color;
} Entity;

Entity* InitEntity(Entity* e, Vector2f pos[3], float angle, u32 color);

int EntityOnEntity(Vector2f pos1[3], Vector2f pos2[3]);

#endif