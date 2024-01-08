#ifndef POWERUP_H
#define POWERUP_H

#include "stds/animation.h"
#include "stds/sound.h"
#include "ball.h"
#include "commons.h"
#include "score_item.h"

extern App_T app;
extern Entity_T* paddle;
extern Stage_T stage;
extern Level_T* currentLevel;

extern Entity_T* addPowerup(float, float, int, int);

extern void powerupUpdate(Entity_T*);

extern void powerupDraw(const Entity_T*);

extern void powerupDie(Entity_T*);

extern void powerupLargeActivate(Entity_T*);

extern void powerupLargeDeactivate(Entity_T*);

extern void powerupCoinActivate(Entity_T*);

extern void powerupLifeActivate(Entity_T*);

extern void powerupMultiActivate(Entity_T*);

#endif
