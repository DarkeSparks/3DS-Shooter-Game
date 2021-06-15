#include "Entity.h"

Entity* InitEntity(Entity* e, Vector2f pos[3], float angle, u32 color) {
    for (int i = 0; i < 3; i++) e->pos[i] = pos[i];
    e->angle = angle;
    e->color = color;

    return e;
}