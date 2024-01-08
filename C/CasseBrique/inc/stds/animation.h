#ifndef ANIMATION_H
#define ANIMATION_H

#include "draw.h"
#include "stds.h"

extern App_T app;

extern Animation_T* addSpritesheet(const char* fileDirectory, int n, float frameTime, int startX, int startY);

extern Animation_T* addAnimation(const char* filesDirectory, int n, float frameTime);

extern void animationUpdate(Animation_T* animation);

extern void animationDraw(const Animation_T* animation);

extern void animationDie(Animation_T* animation);

#endif
