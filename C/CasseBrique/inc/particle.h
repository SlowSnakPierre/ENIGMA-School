#ifndef PARTICLE_H
#define PARTICLE_H

#include "stds/animation.h"
#include "stds/draw.h"
#include "commons.h"

extern App_T app;
extern Particle_T addParticle(float, float, float, float, float, float, int, int, int, int, int, int, int, float, int);
extern Particle_T *addAnimatedParticle(float, float, float, float, float, float, int, int, Animation_T *);
extern void updateParticle(Particle_T *);
extern void drawParticle(const Particle_T *);
extern void removeParticle(const Particle_T *);
#endif