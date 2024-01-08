#ifndef TRAIL_H
#define TRAIL_H

#include "draw.h"
#include "stds.h"

extern App_T app;

extern void addTrail(const Entity_T *parentEntity, int alphaDecayRate, int startingAlpha, bool isTexture, SDL_RendererFlip flip);
extern void updateTrail(Trail_T *t);
extern void drawTrail(const Trail_T *t);

#endif