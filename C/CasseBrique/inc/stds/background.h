#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "draw.h"
#include "stds.h"

extern App_T app;

void initParallaxBackground(const char* bgDirectory, size_t n, float defaultScrollSpeeds,
                            const float modifiedScrollSpeed[], bool isInfinite);

extern void parallaxBackgroundUpdate(const ParallaxBackground_T* parallax);

extern void parallaxBackgroundDraw(const ParallaxBackground_T* parallax);

extern Background_T* initBackground(const char* bgDirectory);

extern void backgroundDraw(const Background_T* bg);

extern void backgroundDie(Background_T* bg);

#endif
