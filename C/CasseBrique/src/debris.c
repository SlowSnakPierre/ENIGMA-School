#include "../inc/debris.h"

void addDebris(const Entity_T* entity) {
    const int w = entity->w >> 4;
    const int h = entity->h >> 4;

    for (int y = 0; y <= h * 2; y += h) {
        for (int x = 0; x <= w * 2; x += w) {
            Debris_T* d = malloc(sizeof(Debris_T));
            memset(d, 0, sizeof(Debris_T));
            stage.debrisTail->next = d;
            stage.debrisTail = d;

            d->x = entity->x + entity->w / 2;
            d->y = entity->y + entity->h / 2;
            d->dx = randomFloat(-5.0f, 5.0f);
            d->dy = randomFloat(1.0f, 2.0f);
            d->texture = entity->texture[0];

            d->rect.x = x;
            d->rect.y = y;
            d->rect.w = w;
            d->rect.h = h;
        }
    }
}

void updateDebris(Debris_T* entity) {
    entity->x += entity->dx;
    entity->y += entity->dy;

    entity->dy += 0.5f;

    if (entity->y > app.SCREEN_HEIGHT) {
        entity->flags |= DEATH_MASK;
    }
}

void drawDebris(const Debris_T* entity) {
    blitRect(entity->texture, &entity->rect, entity->x, entity->y, false);
}

void removeDebris(Debris_T* entity) {
    free(entity);
}
