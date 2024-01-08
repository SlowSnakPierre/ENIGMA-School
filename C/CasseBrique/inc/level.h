#ifndef LEVEL_H
#define LEVEL_H

#include "stds/draw.h"
#include "stds/particle_system.h"
#include "stds/sound.h"
#include "ball.h"
#include "brick.h"
#include "commons.h"
#include "debris.h"
#include "paddle.h"
#include "powerup.h"
#include "score_item.h"
#include "transition.h"

extern Level_T *currentLevel;
extern Entity_T *paddle;
extern ParticleSystem_T *ps;
extern Stage_T stage;

extern Level_T *addLevel(int);
extern void updateLevel(void);
extern void drawLevel(void);
extern void removeBalls(void);
extern void setNextLevel(void);
extern void loadLevelMusic(int);

#endif
