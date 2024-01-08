#ifndef PADDLE_H
#define PADDLE_H

#include "stds/draw.h"
#include "commons.h"

extern Entity_T *paddle;
extern App_T app;
extern Stage_T stage;

extern void initPaddle(void);
extern void updatePaddle(void);
extern void drawPaddle(void);
extern void removePaddle(void);

#endif