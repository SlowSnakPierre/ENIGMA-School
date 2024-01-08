#ifndef BRICKS_H
#define BRICKS_H

#include "stds/animation.h"
#include "stds/draw.h"
#include "commons.h"

extern Entity_T *addBrick(float, float, int, int);
extern void updateBrick(Entity_T *);
extern void drawBrick(const Entity_T *);
extern void removeBrick(Entity_T *);

#endif