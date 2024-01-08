#ifndef DRAW_H
#define DRAW_H

#include "stds.h"

extern App_T app;

extern void prepareScene(void);

extern void presentScene(void);

extern void blitRect(SDL_Texture* texture, const SDL_Rect* src, float x, float y, bool cameraOffset);

extern void blitTexture(SDL_Texture* texture, float x, float y, bool isCenter, bool cameraOffset);

extern void blitTextureRotated(SDL_Texture* texture, float x, float y, int angle, SDL_RendererFlip flip, bool cameraOffset);

extern void blitTextureColorScaled(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, int angle,
                                   SDL_RendererFlip flip, const SDL_Color* c, bool cameraOffset);

extern void blitTextureScaled(SDL_Texture* texture, float x, float y, float scaleX, float scaleY, int angle,
                              SDL_RendererFlip flip, bool cameraOffset);

extern void drawRect(SDL_Rect* rect, const SDL_Color* c, bool isFilled, bool cameraOffset);

extern void drawFrect(SDL_FRect* frect, const SDL_Color* c, bool isFilled, bool cameraOffset);

extern void drawRectStroke(int x, int y, int w, int h, int thickness, const SDL_Color* c, bool cameraOffset);

extern void drawCircle(int centerX, int centerY, int radius, const SDL_Color* c);

extern void fillCircle(int centerX, int centerY, int radius, const SDL_Color* c);

extern void drawLine(float x1, float y1, float x2, float y2, const SDL_Color* c);

extern SDL_Texture* loadTexture(const char* directory);

extern SDL_Color combineFadeColor(FadeColor_T* fadeColor);

#endif
