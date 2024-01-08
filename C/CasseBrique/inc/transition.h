#ifndef TRANSITION_H
#define TRANSITION_H

#include "stds/draw.h"
#include "commons.h"
#include "level.h"

extern App_T app;

extern void activateTransition(bool);
extern void updateTransition(void);
extern void drawTransition(void);

#endif