#include "Player.h"

Player* InitPlayer(Player* pl, Vector2f pos[3], float angle, u32 color, short health) {
    pl->e = *InitEntity(&pl->e, pos, angle, color);
    pl->health = health;

    pl->didMove = 0;

    return pl;
}

void TeleportPlayer(Player* pl, const Vector2f screenSize) {
    int i;
    // TP On X
    float poses[3];
    float Ltp, Stp;

    for (i = 0; i < 3; i++) poses[i] = pl->e.pos[i].x;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp < -5) 
        for (i = 0; i < 3; i++) {
            pl->e.pos[i].x += screenSize.x + 25;
        }
    

    if (Stp > screenSize.x) 
        for (i = 0; i < 3; i++) {
            pl->e.pos[i].x -= screenSize.x + 25;
        }
    

    //TP On Y
    for (i = 0; i < 3; i++) poses[i] = pl->e.pos[i].y;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp < -5) 
        for (i = 0; i < 3; i++) {
            pl->e.pos[i].y += screenSize.y + 25;
        }
    

    if (Stp > screenSize.y) 
        for (i = 0; i < 3; i++) {
            pl->e.pos[i].y -= screenSize.y + 25;
        }
    
}

void MovePlayer(Player* pl, Vector2f pos) {
    const float angleSpeed = 0.075f * 4;

    pl->e.angle = atan2(pos.x, pos.y) + DEGTORAD(90);

    /* if (ButtonHeld(KEY_L)) {
        pl->didMove = 1;

        pl->e.angle -= angleSpeed;

        // if (pl->e.angle < 0) pl->e.angle += 2 * M_PI;

        pl->deltaPos = SetVector2f(cos(pl->e.angle)*5, sin(pl->e.angle)*5);
    } */

    //if (ButtonHeld(KEY_A))  
        // if (pl->e.angle > 2 * M_PI) pl->e.angle -= 2 * M_PI;

    

    //if (ButtonHeld(KEY_CPAD_UP))   {
    
    if (abs(pos.x) > 0.0125f || abs(pos.y) > 0.0125f) {
        pl->didMove = 1;
        
        pl->deltaPos = SetVector2f(cos(pl->e.angle)*5, sin(pl->e.angle)*5);

        for (int i = 0; i < 3; i++) {
            pl->e.pos[i].x -= pl->deltaPos.x * angleSpeed;
            pl->e.pos[i].y -= pl->deltaPos.y * angleSpeed; 
        }
    }
    //}
}

void SpawnBullet(Player* pl, Bullet* b) {
    if (ButtonDown(KEY_A) && pl->didShoot == 0) {
        b = InitBullet(b, pl->e.pos, pl->e.angle, C2D_Color32(0xE0, 0xDB, 0x3A, 0xFF));
        pl->didShoot = 1;
    }

    pl->e.color = (pl->didShoot == 1) ? C2D_Color32(0x0A, 0x29, 0xB0, 0xFF) : C2D_Color32(0x3A, 0x59, 0xE0, 0xFF);
}

void DestroyBullet(Player* pl, Bullet* b, Vector2f screenSize) {
    int i;
    // TP On X
    float poses[3];
    float Ltp, Stp;


    for (i = 0; i < 3; i++) poses[i] = b->e.pos[i].x;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp < -5 || Stp > screenSize.x) {
        for (i = 0; i < 3; i++) b->e.pos[i] = pl->e.pos[i];
        pl->didShoot = 0;
    }
    

    //TP On Y
    for (i = 0; i < 3; i++) poses[i] = b->e.pos[i].y;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp < -5 || Stp > screenSize.y) {
        for (i = 0; i < 3; i++) b->e.pos[i] = pl->e.pos[i];
        pl->didShoot = 0;
    }

    if (pl->didShoot == 1) MoveBullet(b);
    else {
        for (int i = 0; i < 3; i++ ) { b->e.pos[i].x = pl->e.pos[i].x; b->e.pos[i].y = pl->e.pos[i].y; }
        b->e.angle = pl->e.angle;
    }
}