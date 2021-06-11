#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

typedef struct Bullet {
    unsigned short hitEntity : 1;

    Vector2f deltaPos;

    Entity e;
} Bullet;

Bullet* InitBullet(Bullet* b, Vector2f pos[3], float angle, u32 color);

void MoveBullet(Bullet* b);

#endif