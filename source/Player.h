#ifndef PLAYER_H
#define PLAYER_H

#include <citro2d.h>
#include "Math.h"
#include "Game.h"
#include "Entity.h"

#include "Bullet.h"

typedef struct Player {
    short health : 4;
    unsigned short didShoot : 1;
    unsigned short didMove : 1;
    Vector2f deltaPos;
    Entity e;
} Player;

Player* InitPlayer(Player* pl, Vector2f pos[3], float angle, u32 color, short health);
void TeleportPlayer(Player* pl, const Vector2f screenSize);
void MovePlayer(Player* pl);

void SpawnBullet(Player* pl, Bullet* b);
void DestroyBullet(Player* pl, Bullet* b, Vector2f screenSize);

#endif