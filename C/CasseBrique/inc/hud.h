#ifndef HUD_H
#define HUD_H

#include "stds/button.h"
#include "stds/draw.h"
#include "stds/text.h"
#include "commons.h"
#include "main.h"

extern ParticleSystem_T *ps;
extern App_T app;
extern Stage_T stage;
extern Entity_T *paddle;

extern void initHUD(void);
extern void updateHUD(void);
extern void drawHUD(void);
extern void pausedHUD(void);
extern void initMenu(void);
extern void updateMenu(void);
extern void drawMenu(const SDL_Color *);

#endif