#include "../../inc/stds/animation.h"

static char inputBuffer[MAX_BUFFER_SIZE];

Animation_T* addSpritesheet(const char* fileDirectory, const int n, const float frameTime, const int startX,
                            const int startY) {
    Animation_T* a = malloc(sizeof(Animation_T));

    if (a == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n", SDL_GetError());
        exit(1);
    }

    memset(a, 0, sizeof(Animation_T));

    a->numberOfFrames = n;
    a->currentTexture = loadTexture(fileDirectory);
    a->frameDelay = frameTime;
    a->frameTimer = frameTime * FPS;
    a->startX = startX;
    a->startY = startY;

    SDL_QueryTexture(a->currentTexture, NULL, NULL, &a->spriteSheetWidth, &a->spriteSheetHeight);

    a->w = a->spriteSheetWidth / n;
    a->h = a->spriteSheetHeight;

    a->currentFrameId = 0;
    a->idFlags |= SPRITE_SHEET_MASK;
    a->flags |= ANIMATION_ACTIVE_MASK;

    return a;
}

Animation_T* addAnimation(const char* filesDirectory, const int n, const float frameTime) {
    Animation_T* a = malloc(sizeof(Animation_T));

    if (a == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for animation_t. %s.\n", SDL_GetError());
        exit(2);
    }

    memset(a, 0, sizeof(Animation_T));
    a->frames = malloc(sizeof(SDL_Texture *) * n);

    if (a->frames == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for a->frames. %s.\n", SDL_GetError());
        exit(3);
    }

    a->numberOfFrames = n;
    a->frameDelay = frameTime;
    a->frameTimer = frameTime * FPS;
    a->currentFrameId = 0;

    SDL_QueryTexture(a->currentTexture, NULL, NULL, &a->w, &a->h);
    a->idFlags |= STD_ANIMATION_MASK;
    a->flags |= ANIMATION_ACTIVE_MASK;

    for (int i = 0; i < a->numberOfFrames; i++) {
        int NUM_DIGITS = 3;
        char numberBuffer[NUM_DIGITS];
        const char* fileExtsn = ".png";
        sprintf(numberBuffer, "%d", i);
        strcpy(inputBuffer, filesDirectory);
        strcat(inputBuffer, numberBuffer);
        const char* file_extsn = ".png";
        strcat(inputBuffer, file_extsn);
        const char* fileNameExt = strcat(inputBuffer, fileExtsn);
        a->frames[i] = loadTexture(fileNameExt);
        memset(inputBuffer, '\0', sizeof(inputBuffer));
    }
    a->currentTexture = a->frames[0];
    a->defaultTexture = a->frames[0];

    return a;
}

void animationUpdate(Animation_T* animation) {
    if (animation->flags & ANIMATION_ACTIVE_MASK)
        animation->frameTimer -= 1;

    if (animation->frameTimer < 0) {
        animation->frameTimer = animation->frameDelay * FPS;
        animation->currentFrameId += 1;

        if (animation->idFlags & SPRITE_SHEET_MASK) {
            animation->spliceX += animation->spriteSheetWidth / animation->numberOfFrames;
        }
        else {
            animation->currentTexture = animation->frames[animation->currentFrameId];
        }

        if (animation->currentFrameId >= animation->numberOfFrames) {
            animation->currentFrameId = 0;
            if (animation->idFlags & SPRITE_SHEET_MASK) {
                animation->spliceX = 0;
            }
            else {
                animation->currentFrameId = 0;
            }

            if (animation->cycleOnce) {
                animation->flags ^= ANIMATION_ACTIVE_MASK;
                animation->cycleOnce = false;
                animation->currentFrameId = 0;
            }
        }
    }
}

void animationDraw(const Animation_T* animation) {
    if (animation->flags & ANIMATION_ACTIVE_MASK) {
        if (animation->idFlags & STD_ANIMATION_MASK) {
            blitTextureRotated(animation->frames[animation->currentFrameId], animation->posX, animation->posY,
                               animation->angle, animation->flip, true);
        }
        else if (animation->idFlags & SPRITE_SHEET_MASK) {
            const SDL_Rect curr_rect = {animation->spliceX, animation->spliceY, animation->w, animation->h};
            blitRect(animation->currentTexture, &curr_rect, animation->posX, animation->posY, true);
        }
    }
}

void animationDie(Animation_T* animation) {
    for (int i = 0; i < animation->numberOfFrames; i++) {
        SDL_DestroyTexture(animation->frames[i]);
    }

    SDL_DestroyTexture(animation->currentTexture);
    free(animation->frames);
    free(animation);
}
