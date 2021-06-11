#ifndef ENEMY_H
#define ENEMY_H

#include <citro2d.h>
#include "Math.h"
#include "Game.h"
#include "Entity.h"

typedef struct Enemy {
    unsigned short side : 1;
    unsigned short doesShoot : 1;
    unsigned short id;
    float speed;
    Entity e;
} Enemy;

Enemy* InitEnemy(Enemy* en, Vector2f pos[3], float angle, u32 color);
void   MoveEnemy(Enemy* en);
void   TeleportEnemy(Enemy* en, const Vector2f screenSize);
void   RotateEnemy(Enemy* en, Entity e);

void MoveHitEnemy(Enemy* es);

#endif