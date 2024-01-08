#include "../../inc/stds/collision.h"

enum CollisionSide checkAabbCollision(Entity_T* a, const Entity_T* b) {
    const float w = 0.5f * (b->w + a->w);
    const float h = 0.5f * (b->h + a->h);
    const float dx = b->x + b->w / 2.0f - (a->x + a->w / 2.0f);
    const float dy = b->y + b->h / 2.0f - (a->y + a->h / 2.0f);

    if (fabs(dx) < w && fabs(dy) < h) {
        const float wy = w * dy;
        const float hx = h * dx;

        if (wy >= hx) {
            if (wy > -hx) {
                a->y = b->y - a->h;
                return SIDE_TOP;
            }
            a->x = b->x + b->w;
            return SIDE_RIGHT;
        }

        if (wy > -hx) {
            a->x = b->x - a->w;
            return SIDE_LEFT;
        }

        a->y = b->y + b->h;

        return SIDE_BOTTOM;
    }

    return SIDE_NONE;
}

bool check_intersection(const float x1, const float y1, const int w1, const int h1, const float x2, const float y2, const int w2, const int h2) {
    return MAX(x1, x2) < MIN(x1 + w1, x2 + w2) && MAX(y1, y2) < MIN(y1 + h1, y2 + h2);
}
