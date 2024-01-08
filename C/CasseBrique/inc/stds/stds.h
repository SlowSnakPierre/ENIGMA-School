#ifndef STDS_H
#define STDS_H

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "stddefine.h"
#include "structs.h"

#define MAX_INT_DIGITS 11
#define DEBUG          1

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a: b)
#define MAX3(a, b, c) (MAX(MAX(a, b), c))
#define MIN3(a, b, c) (MIN(MIN(a, b), c))

extern int randomInt(int min, int max);
extern float randomFloat(float min, float max);
extern void clamp(int *n, int min, int max);
extern void calcSlope(int x1, int y1, int x2, int y2, float *xSlope, float *ySlope);
extern float getAngle(int x1, int y1, int x2, int y2);
extern int getDistance(int x1, int y1, int x2, int y2);
extern void print(const char * s, ...);
extern float toRadians(float degreeAngle);
extern float toDegrees(float radianAngle);
extern bool isMouseOverRect(float x, float y, SDL_Rect rect);
extern char *strSubstring(const char *str, int first, int last);
extern int strIndexOf(const char *s, const char *searchStr);
extern char *strcatInt(const char *s, int n);
#endif