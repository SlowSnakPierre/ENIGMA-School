#ifndef GAME_H
#define GAME_H

#include "stds.h"

extern App_T app;

extern void prepareScene(void);

extern void processInput(void);

extern void presentScene(void);

extern void loop(void);

extern void initAppStructures(void);

extern void initWindowFps(void);

#endif
