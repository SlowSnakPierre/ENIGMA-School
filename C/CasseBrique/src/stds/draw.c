#include "../../inc/stds/draw.h"

static SDL_Texture* getTexture(const char*);

static void cacheTexture(const char*, SDL_Texture*);

void prepareScene() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
    SDL_RenderClear(app.renderer);
}

void presentScene() {
    SDL_RenderPresent(app.renderer);
}

void blitTexture(SDL_Texture* texture, const float x, const float y, const bool isCenter, const bool cameraOffset) {
    SDL_FRect dest;

    dest.x = cameraOffset ? x - app.camera.x : x;
    dest.y = cameraOffset ? y - app.camera.y : y;

    int w, h;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    dest.w = (float)w;
    dest.h = (float)h;

    if (isCenter) {
        dest.x -= dest.w / 2.0f;
        dest.y -= dest.h / 2.0f;
    }

    SDL_RenderCopyF(app.renderer, texture, NULL, &dest);
}

void blitRect(SDL_Texture* texture, const SDL_Rect* src, const float x, const float y, const bool cameraOffset) {
    SDL_FRect dest;
    dest.x = cameraOffset ? x - app.camera.x : x;
    dest.y = cameraOffset ? y - app.camera.y : y;

    dest.w = src->w;
    dest.h = src->h;
    SDL_RenderCopyF(app.renderer, texture, src, &dest);
}

void blitTextureRotated(SDL_Texture* texture, const float x, const float y, const int angle,
                        const SDL_RendererFlip flip,
                        const bool cameraOffset) {
    SDL_FRect dest;
    dest.x = cameraOffset ? x - app.camera.x : x;
    dest.y = cameraOffset ? y - app.camera.y : y;
    int w, h;

    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    dest.w = (float)w;
    dest.h = (float)h;

    SDL_RenderCopyExF(app.renderer, texture, NULL, &dest, angle, NULL, flip);
}

void blitTextureColorScaled(SDL_Texture* texture, const float x, const float y, const float scaleX, const float scaleY,
                            const int angle, const SDL_RendererFlip flip, const SDL_Color* c, const bool cameraOffset) {
    int textureWidth = 0;
    int textureHeight = 0;

    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    SDL_FRect destRect;

    destRect.x = cameraOffset ? x - app.camera.x : x;
    destRect.y = cameraOffset ? y - app.camera.y : y;
    destRect.w = textureWidth * scaleX;
    destRect.h = textureHeight * scaleY;

    if (c != NULL) {
        SDL_SetTextureColorMod(texture, c->r, c->g, c->b);
        SDL_SetTextureAlphaMod(texture, c->a);
    }

    SDL_RenderCopyExF(app.renderer, texture, NULL, &destRect, angle, NULL, flip);
}

void blitTextureScaled(SDL_Texture* texture, const float x, const float y, const float scaleX, const float scaleY,
                       const int angle, const SDL_RendererFlip flip, const bool cameraOffset) {
    blitTextureColorScaled(texture, x, y, scaleX, scaleY, angle, flip, NULL, cameraOffset);
}

void drawRect(SDL_Rect* rect, const SDL_Color* c, const bool isFilled, const bool cameraOffset) {
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app.renderer, c->r, c->g, c->b, c->a);

    if (cameraOffset) {
        rect->x -= app.camera.x;
        rect->y -= app.camera.y;
    }

    if (isFilled) {
        SDL_RenderFillRect(app.renderer, rect);
    }
    else {
        SDL_RenderDrawRect(app.renderer, rect);
    }
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void drawFrect(SDL_FRect* frect, const SDL_Color* c, const bool isFilled, const bool cameraOffset) {
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(app.renderer, c->r, c->g, c->b, c->a);

    if (cameraOffset) {
        frect->x -= app.camera.x;
        frect->y -= app.camera.y;
    }

    if (isFilled) {
        SDL_RenderFillRectF(app.renderer, frect);
    }
    else {
        SDL_RenderDrawRectF(app.renderer, frect);
    }

    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

void drawRectStroke(int x, int y, const int w, const int h, const int thickness, const SDL_Color* c,
                    const bool cameraOffset) {
    if (thickness <= 0) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Error: thickness %d cannot be a negative or zero value!", thickness);
        exit(7);
    }

    if (cameraOffset) {
        x += app.camera.x;
        y += app.camera.y;
    }

    SDL_Rect r1 = {x, y, w, thickness};
    SDL_Rect r2 = {x, y, thickness, h};
    SDL_Rect r3 = {x, cameraOffset ? h - thickness + app.camera.y : h - thickness, w, thickness};
    SDL_Rect r4 = {cameraOffset ? w - thickness + app.camera.x : w - thickness, y, thickness, h};

    drawRect(&r1, c, true, cameraOffset);
    drawRect(&r2, c, true, cameraOffset);
    drawRect(&r3, c, true, cameraOffset);
    drawRect(&r4, c, true, cameraOffset);
}

void drawLine(const float x1, const float y1, const float x2, const float y2, const SDL_Color* c) {
    SDL_SetRenderDrawColor(app.renderer, c->r, c->g, c->b, c->a);
    SDL_RenderDrawLine(app.renderer, (int)x1, (int)y1, (int)x2,
                       (int)y2);
}

void drawCircle(const int centerX, const int centerY, const int radius, const SDL_Color* c) {
    const int diameter = radius * 2;

    int x = radius - 1;
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = tx - diameter;

    SDL_SetRenderDrawColor(app.renderer, c->r, c->g, c->b, c->a);
    while (x >= y) {
        SDL_RenderDrawPoint(app.renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(app.renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(app.renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(app.renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(app.renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(app.renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(app.renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(app.renderer, centerX - y, centerY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += tx - diameter;
        }
    }
}

void fillCircle(const int centerX, const int centerY, const int radius, const SDL_Color* c) {
    int offsetx = 0;
    int offsety = radius;
    int d = radius - 1;
    int status = 0;
    SDL_SetRenderDrawColor(app.renderer, c->r, c->g, c->b, c->a);

    while (offsety >= offsetx) {
        status +=
                SDL_RenderDrawLine(app.renderer, centerX - offsety, centerY + offsetx, centerX + offsety,
                                   centerY + offsetx);
        status +=
                SDL_RenderDrawLine(app.renderer, centerX - offsetx, centerY + offsety, centerX + offsetx,
                                   centerY + offsety);
        status +=
                SDL_RenderDrawLine(app.renderer, centerX - offsetx, centerY - offsety, centerX + offsetx,
                                   centerY - offsety);
        status +=
                SDL_RenderDrawLine(app.renderer, centerX - offsety, centerY - offsetx, centerX + offsety,
                                   centerY - offsetx);

        if (status < 0) {
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

SDL_Color combineFadeColor(FadeColor_T* fadeColor) {
    if (fadeColor->time <= 1.0f && fadeColor->isFirstColor) {
        fadeColor->time = fadeColor->time + fadeColor->alpha;
    }
    else {
        fadeColor->isFirstColor = false;
    }

    if (fadeColor->time >= 0.0f && !fadeColor->isFirstColor) {
        fadeColor->time = fadeColor->time - fadeColor->alpha;
    }
    else {
        fadeColor->isFirstColor = true;
    }

    int r = (int)(fadeColor->time * fadeColor->c2.r + (1.0f - fadeColor->time) * fadeColor->c1.r);
    int g = (int)(fadeColor->time * fadeColor->c2.g + (1.0f - fadeColor->time) * fadeColor->c1.g);
    int b = (int)(fadeColor->time * fadeColor->c2.b + (1.0f - fadeColor->time) * fadeColor->c1.b);

    SDL_Color c;
    clamp(&r, 0, 255);
    clamp(&g, 0, 255);
    clamp(&b, 0, 255);

    c.r = r;
    c.g = g;
    c.b = b;
    c.a = 1;

    return c;
}

SDL_Texture* loadTexture(const char* directory) {
    SDL_Texture* texture = getTexture(directory);

    if (texture == NULL) {
        texture = IMG_LoadTexture(app.renderer, directory);
        if (texture == NULL) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                        "Error: could not load image %s. Error Code: %s.\n", directory, SDL_GetError());
            exit(8);
        }

        cacheTexture(directory, texture);
    }

    return texture;
}

static SDL_Texture* getTexture(const char* fileName) {
    for (const Texture_T* t = app.textureHead.next; t != NULL; t = t->next) {
        if (strcmp(t->name, fileName) == 0) {
            return t->texture;
        }
    }

    return NULL;
}

static void cacheTexture(const char* fileName, SDL_Texture* sdlTexture) {
    Texture_T* texture = malloc(sizeof(Texture_T));

    if (texture == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for texture_t. %s.\n",
                    SDL_GetError());
        exit(9);
    }

    memset(texture, 0, sizeof(Texture_T));
    app.textureTail->next = texture;
    app.textureTail = texture;

    strncpy(texture->name, fileName, MAX_FILE_NAME_LEN);
    texture->texture = sdlTexture;
}
