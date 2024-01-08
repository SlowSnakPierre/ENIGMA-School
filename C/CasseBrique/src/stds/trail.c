#include "../../inc/stds/trail.h"

void addTrail(const Entity_T* parentEntity, const int alphaDecayRate, const int startingAlpha, const bool isTexture, const SDL_RendererFlip flip) {
    Trail_T* t = malloc(sizeof(Trail_T));

    if (t == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for trail_t. %s.\n",
                    SDL_GetError());
        exit(20);
    }

    memset(t, 0, sizeof(Trail_T));

    t->x = parentEntity->x;
    t->y = parentEntity->y;
    t->flip = flip;
    t->isTexture = isTexture;

    if (parentEntity->animation != NULL) {
        t->texture = parentEntity->animation->frames[parentEntity->animation->currentFrameId];
    }
    else {
        t->texture = parentEntity->texture[0];
    }

    t->alpha = startingAlpha;
    t->alphaDecayRate = alphaDecayRate;

    app.trailTail->next = t;
    app.trailTail = t;
}

void updateTrail(Trail_T* t) {
    t->alpha -= t->alphaDecayRate;
    if (t->alpha <= 0) {
        t->flags |= DEATH_MASK;
    }
}

void drawTrail(const Trail_T* t) {
    if (!t->isTexture) {
        SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_BLEND);
    }

    SDL_SetTextureAlphaMod(t->texture, t->alpha);
    blitTextureRotated(t->texture, t->x, t->y, 0, t->flip, true);

    if (!t->isTexture) {
        SDL_SetTextureBlendMode(t->texture, SDL_BLENDMODE_NONE);
    }
}
