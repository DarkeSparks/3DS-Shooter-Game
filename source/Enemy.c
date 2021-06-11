#include "Enemy.h"

Enemy* InitEnemy(Enemy* en, Vector2f pos[3], float angle, u32 color) {
    en->e = *InitEntity(&en->e, pos, angle, color);
    en->side = rand() % 2;
    en->speed = (2.5f + RANDFLOAT(1.0f)) / 1.5f;

    return en;
}

void MoveEnemy(Enemy* en) {
    for (int i = 0; i < 3; i++) {
        if (en->side == 0) en->e.pos[i].y += en->speed;
        else en->e.pos[i].y -= en->speed;
    }
}

void TeleportEnemy(Enemy* en, const Vector2f screenSize) {
    int i;

    float poses[3];
    float Ltp, Stp;

    float randomPoses = (rand() % 2 == 0) ? RANDFLOAT(screenSize.x/3.5f) : -RANDFLOAT(screenSize.x/3.5f);
    float randScreenPoses = (rand() % 2 == 0) ? 100.0f : 200.0f;

    //TP On X
    for (i = 0; i < 3; i++) poses[i] = en->e.pos[i].x;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp <= 0 + 25) 
        for (i = 0; i < 3; i++) {
            en->e.pos[i].x += randScreenPoses;
        }
    

    if (Stp >= screenSize.x - 25) 
        for (i = 0; i < 3; i++) {
            en->e.pos[i].x -= randScreenPoses;
        }

    //TP On Y
    for (i = 0; i < 3; i++) poses[i] = en->e.pos[i].y;

    Ltp = Largest(poses, 3), Stp = Smallest(poses, 3);

    if (Ltp < -5) {
        for (i = 0; i < 3; i++) {
            en->e.pos[i].y += screenSize.y + 25;

            en->e.pos[i].x += randomPoses;
        }

        en->side = rand() % 2;
    }
    

    if (Stp > screenSize.y) {
        for (i = 0; i < 3; i++) {
            en->e.pos[i].y -= screenSize.y + 25;

            en->e.pos[i].x += randomPoses;
        }

        en->side = rand() % 2;
    }
    
}

void RotateEnemy(Enemy* en, Entity e) {
	float avX = ((en->e.pos[0].x + en->e.pos[1].x + en->e.pos[2].x) / 3) - ((e.pos[0].x + e.pos[1].x + e.pos[2].x) / 3);
	float avY = ((en->e.pos[0].y + en->e.pos[1].y + en->e.pos[2].y) / 3) - ((e.pos[0].y + e.pos[1].y + e.pos[2].y) / 3);

	//Vector2f dif = SetVector2f(e->pos[0].x - pl->e.pos[0].x, (e->pos[0].y + 7) - (pl->e.pos[0].y + 10));
	en->e.angle = atan2(avY, avX);
	
}

void MoveHitEnemy(Enemy* es) {
    Vector2f pos[3] = {
		SetVector2f(200 / 1.375f + 50, 110 / 1.375f + 25),
		SetVector2f(188 / 1.375f + 50, 135 / 1.375f + 25),
		SetVector2f(213 / 1.375f + 50, 135 / 1.375f + 25)
	};

    pos[0].y += 12.5f/2;
	pos[1].x -= 12.5f/2;
	pos[2].x += 12.5f/2;

	for (int i = 0; i < 3; i++) pos[i].x -= 75;

    es = InitEnemy(es, pos, DEGTORAD(90),  C2D_Color32(0xE0, 0x3F, 0x3A, 0xFF) );

	float randFloat = RANDFLOAT(12.5f);

    for (int i = 0; i < 3; ++i) es->e.pos[i].y -= 120 + randFloat;
}