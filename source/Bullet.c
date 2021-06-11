#include "Bullet.h"

Bullet* InitBullet(Bullet* b, Vector2f pos[3], float angle, u32 color) {
    b->e = *InitEntity(&b->e, pos, angle, color);
    
    return b;
}

void MoveBullet(Bullet* b) {
    b->deltaPos = SetVector2f(cos(b->e.angle)*5, sin(b->e.angle)*5);

    for (int i = 0; i < 3; i++) {
        b->e.pos[i].x -= (b->deltaPos.x) * 1.125f;
        b->e.pos[i].y -= (b->deltaPos.y) * 1.125f; 
    }
}