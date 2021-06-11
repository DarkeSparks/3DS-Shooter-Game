#include "Rotated.h"
#include <stdlib.h>

void DrawRotatedTriangle(Entity e, Vector2f origin, float angle, u32 color) {
    float a1, b1, a2, b2, a3, b3, p = e.pos[1].x + origin.x, q = e.pos[1].y - origin.y;

    a1 = p + (e.pos[1].x - p) * cos(angle) - (e.pos[1].y - q) * sin(angle);
    b1 = q + (e.pos[1].x - p) * sin(angle) + (e.pos[1].y - q) * cos(angle);
    a2 = p + (e.pos[0].x - p) * cos(angle) - (e.pos[0].y - q) * sin(angle);
    b2 = q + (e.pos[0].x - p) * sin(angle) + (e.pos[0].y - q) * cos(angle);
    a3 = p + (e.pos[2].x - p) * cos(angle) - (e.pos[2].y - q) * sin(angle);
    b3 = q + (e.pos[2].x - p) * sin(angle) + (e.pos[2].y - q) * cos(angle);

    e.pos[0].x = a1;
    e.pos[0].y = b1;
    e.pos[1].x = a2;
    e.pos[1].y = b2;
    e.pos[2].x = a3;
    e.pos[2].y = b3;

    C2D_DrawTriangle(e.pos[0].x, e.pos[0].y, color, e.pos[1].x, e.pos[1].y, color, e.pos[2].x, e.pos[2].y, color, 0);
    //C2D_DrawTriangle(a1, b1, color, a2, b2, color, a3, b3, color, 0);
    //C2D_DrawCircleSolid(p, q, 0, 2, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF));
}

void DrawLineLA(Vector2f pos, float length, float angle, float thickness) {
	angle = abs(angle);

	if (angle > 360) angle = 0;
	if (angle < 0) angle = 360;

	Vector2f pos2 = (Vector2f){ pos.x + length * cos(angle), pos.y + length * sin(angle) };

	C2D_DrawLine(pos.x, pos.y, C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF), pos2.x, pos2.y, C2D_Color32(0xFF, 0xFF, 0xFF, 0xAF), thickness, 0);
}