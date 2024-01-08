#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern App_T app;
extern void initFonts(void);
extern void drawText(float x, float y, int r, int g, int b, const char *fontDirectory, int fontSize, const char *str, ...);
extern void getStringSize(const char *str, const char *fontName, int fontSize, int *storedWidth, int *storedHeight);
#endif