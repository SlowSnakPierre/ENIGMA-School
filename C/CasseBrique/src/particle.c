#include "../inc/particle.h"

Particle_T addParticle(const float x, const float y, const float dx, const float dy, const float decX, const float decY, const int w, const int h, const int angle, const int r,
                        const int g, const int b, const int a, const float delta_alpha, const int id_flags) {
    Particle_T en;

    en.x = x;
    en.y = y;
    en.w = w;
    en.h = h;
    en.dx = dx;
    en.dy = dy;
    en.life = FPS * 3;
    en.deltaAccelX = decX;
    en.deltaAccelY = decY;
    en.animation = NULL;

    const SDL_Color color = {r, g, b, a};

    en.color = color;
    en.deltaAlpha = delta_alpha;
    en.angle = angle;
    en.idFlags |= id_flags | ID_PARTICLE_MASK;
    en.flags |= ID_PARTICLE_MASK;

    en.particleUpdate = updateParticle;
    en.particleDraw = updateParticle;

    return en;
}

Particle_T* addAnimatedParticle(const float x, const float y, const float dx, const float dy, const float decX, const float decY, const int angle,
                                const int id_flags, Animation_T* animation) {
    Particle_T* en = malloc(sizeof(Particle_T));
    memset(en, 0, sizeof(Particle_T));

    en->x = x;
    en->y = y;
    en->animation = animation;

    if (animation->flags & STD_ANIMATION_MASK) {
        en->w = animation->spriteSheetWidth / animation->numberOfFrames;
        en->h = animation->spriteSheetHeight / animation->numberOfFrames;
    }
    else {
        SDL_QueryTexture(animation->currentTexture, NULL, NULL, &en->w, &en->h);
    }

    en->dx = dx;
    en->dy = dy;

    en->life = FPS * 3;
    en->deltaAccelX = decX;
    en->deltaAccelY = decY;

    en->angle = angle;
    en->idFlags |= id_flags | ID_PARTICLE_MASK;

    en->particleUpdate = updateParticle;
    en->particleDraw = drawParticle;

    return en;
}

void updateParticle(Particle_T* e) {
    if (--e->life <= 0) {
        e->flags |= DEATH_MASK;
        return;
    }

    if (floor(e->deltaAccelX) != 0) {
        e->dx *= e->deltaAccelX;
    }

    if (floor(e->deltaAccelY) != 0) {
        e->dy *= e->deltaAccelY;
    }

    if (e->idFlags & ID_P_STAR_MASK) {
        if (e->y < -100.0f) {
            e->flags |= DEATH_MASK;
        }
    }

    int16_t tmp_alpha = (int)(e->color.a + e->deltaAlpha);
    if (tmp_alpha < 0) {
        tmp_alpha = 0;
    }

    e->color.a = tmp_alpha;
    e->x += e->dx;
    e->y += e->dy;
}

void drawParticle(const Particle_T* e) {
    if (e->animation == NULL) {
        SDL_FRect frect = {e->x, e->y, e->w, e->h};

        if (e->idFlags & ID_P_SQUARE_MASK) {
            drawFrect(&frect, &e->color, true, false);
        }
        else if (e->idFlags & ID_P_CIRCLE_MASK) {
            const int r = (int)(frect.w / 2);
            fillCircle((int)frect.x, (int)frect.y, r, &e->color);
        }
    }
    else {
        animationDraw(e->animation);
    }
}
