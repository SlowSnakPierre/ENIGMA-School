#ifndef COLLISION_H
#define COLLISION_H

#include "stds.h"

extern enum CollisionSide checkAabbCollision(Entity_T* a, const Entity_T* b);

extern bool check_intersection(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);

#endif
