#ifndef BUTTON_H
#define BUTTON_H

#include "draw.h"
#include "stds.h"
#include "text.h"

extern void drawButtons(void);

extern Button_T* addButton(float x, float y, int w, int h, bool filled, const char* fontDirectory, int fontSize,
                           const SDL_Color* fontColor, const char* text);

extern Button_T* addButtonTexture(float x, float y, const char* textureDirectory, const char* fontDirectory,
                                  int fontSize, const SDL_Color* color, const char* text);

extern void buttonDraw(Button_T* button);

extern bool isMouseOverButton(const Button_T* button);

extern bool isButtonClicked(const Button_T* button, int mouseCode);

#endif
