#ifndef BALL_H
#define BALL_H

#include "stds/draw.h"
#include "stds/trail.h"
#include "commons.h"
#include "particle.h"

extern ParticleSystem_T *ps;
extern App_T app;
extern Stage_T stage;
extern Level_T* currentLevel;

Entity_T *addBall(float, float, int flags);
void ballUpdate(Entity_T *);
void ballDraw(const Entity_T *);
void ballDestroy(Entity_T *);
#endif