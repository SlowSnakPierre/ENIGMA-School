#ifndef MAIN_H
#define MAIN_H

#include "stds/draw.h"
#include "stds/game.h"
#include "stds/init.h"
#include "stds/particle_system.h"
#include "stds/sound.h"
#include "stds/text.h"
#include "stds/background.h"

#include "ball.h"
#include "commons.h"
#include "debris.h"
#include "hud.h"
#include "level.h"
#include "paddle.h"
#include "particle.h"
#include "powerup.h"

extern App_T app;
extern ParticleSystem_T *ps;
extern Stage_T stage;
extern Entity_T *paddle;
extern Background_T *background;
extern Level_T *currentLevel;

extern void loadLevelMusic(int);

#endif