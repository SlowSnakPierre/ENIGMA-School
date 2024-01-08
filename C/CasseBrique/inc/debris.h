#ifndef DEBIS_H
#define DEBIS_H

#include "stds/draw.h"
#include "commons.h"

extern Stage_T stage;

extern void addDebris(const Entity_T *entity);
extern void updateDebris(Debris_T *entity);
extern void drawDebris(const Debris_T *entity);
extern void removeDebris(Debris_T *entity);

#endif