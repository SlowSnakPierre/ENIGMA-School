#include "../inc/ball.h"

static void checkBounds(Entity_T*);

static void spawnBallParticles(const Entity_T*);

Entity_T* addBall(const float x, const float y, const int flags) {
    Entity_T* b = malloc(sizeof(Entity_T));
    memset(b, 0, sizeof(Entity_T));

    b->x = x;
    b->y = y;
    b->texture[0] = loadTexture("res/img/ball_sprite.png");
    SDL_QueryTexture(b->texture[0], NULL, NULL, &b->w, &b->h);

    b->dx = 0;
    b->dy = BALL_SPEED_DEFAULT;

    b->idFlags |= ID_BALL_MASK;
    b->flags |= flags;
    currentLevel->ballCount++;
    return b;
}

void ballUpdate(Entity_T* b) {
    b->x += b->dx;
    b->y += b->dy;
    checkBounds(b);
}

void ballDraw(const Entity_T* b) {
    blitTexture(b->texture[0], b->x, b->y, false, false);
}

void ballDestroy(Entity_T* b) {
    free(b);
}

static void checkBounds(Entity_T* b) {
    if (b->x < 0) {
        b->x = 0;
        b->dx = -b->dx;
    }
    else if (b->x + b->w > app.SCREEN_WIDTH) {
        b->x -= b->w;
        b->dx = -b->dx;
    }
    else if (b->y < 0) {
        b->y = 0;
        b->dy = -b->dy;
    }
    else if (b->y + b->h > app.SCREEN_HEIGHT) {
        currentLevel->ballCount--;
        spawnBallParticles(b);
        b->flags |= DEATH_MASK;
    }
}

static void spawnBallParticles(const Entity_T* b) {
    for (int i = 0; i < BALL_DEATH_PARTICLES; i++) {
        Particle_T p;
        p.x = b->x + b->w / 2;
        p.y = b->y + b->h / 2;
        p.dx = randomFloat(-5, 5);
        p.dy = randomFloat(-7, 5);
        p.deltaAccelX = p.deltaAccelY = 0;
        p.w = p.h = 3;
        p.color.r = 255;
        p.color.g = p.color.b = 0;
        p.color.a = 255;
        p.deltaAlpha = -3.0f;
        p.idFlags |= ID_P_SQUARE_MASK;
    }
}
