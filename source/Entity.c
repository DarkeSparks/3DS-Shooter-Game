#include "Entity.h"

Entity* InitEntity(Entity* e, Vector2f pos[3], float angle, u32 color) {
    for (int i = 0; i < 3; i++) e->pos[i] = pos[i];
    e->angle = angle;
    e->color = color;

    return e;
}

int EntityOnEntity(Vector2f pos1[3], Vector2f pos2[3]) {
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