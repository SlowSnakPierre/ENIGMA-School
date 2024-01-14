#include "../inc/powerup.h"

#define COIN_SCORE      500
#define LIFE_SCORE      1000
#define POWERUP_DESCENT 3
#define MAX_LIVES       6

Entity_T* addPowerup(const float x, const float y, const int flags, const int identifier) {
    Entity_T* p = malloc(sizeof(Entity_T));
    memset(p, 0, sizeof(Entity_T));

    p->x = x;
    p->y = y;
    p->idFlags |= ID_DEFAULT_POWERUP_MASK;
    p->flags |= flags | POWERUP_INACTIVE;
    p->identifier = identifier;

    Animation_T* a;

    switch (identifier) {
        case MULTI_BALL:
            a = addSpritesheet("res/img/powerup/multi.png", 10, 0.05f, 0, 0);
            break;
        case LARGE_PADDLE:
            a = addSpritesheet("res/img/powerup/large.png", 10, 0.05f, 0, 0);
            break;
        case EXTRA_LIFE:
            a = addSpritesheet("res/img/powerup/extra_life.png", 8, 0.09f, 0, 0);
            break;
        case GOLD_COIN:
            a = addSpritesheet("res/img/powerup/gold_coin.png", 16, 0.05f, 0, 0);
            break;
        default:
            exit(EXIT_ERROR);
    }

    a->flags |= ANIMATION_ACTIVE_MASK;

    p->w = a->w;
    p->h = a->h;
    p->animation = a;

    return p;
}

void powerupUpdate(Entity_T* p) {
    if (p->flags & POWERUP_ACTIVE) {
        if (--p->life < 0) {
            if (p->identifier == LARGE_PADDLE) {
                powerupLargeDeactivate(p);
            }
        }

        return;
    }

    if (p->animation != NULL) {
        p->animation->posX = p->x;
        p->animation->posY = p->y;
        animationUpdate(p->animation);
    }

    p->y += POWERUP_DESCENT;

    if (p->y > app.SCREEN_HEIGHT) {
        p->flags |= DEATH_MASK;
    }
}

void powerupDraw(const Entity_T* p) {
    if (p->animation != NULL && ((p->flags & POWERUP_ACTIVE) == 0)) {
        animationDraw(p->animation);
    }
}

void powerupDie(Entity_T* p) {
    if (p->flags & DEATH_MASK) {
        free(p);
    }
}

void powerupLargeActivate(Entity_T* p) {
    if (paddle->scaleX >= 2.0f) {
        return;
    }

    p->life = FPS * 10;
    p->flags |= POWERUP_ACTIVE;
    paddle->w *= 2;
    paddle->scaleX = 2.0f;
}

void powerupLargeDeactivate(Entity_T* p) {
    paddle->w /= 2;
    paddle->scaleX = 1.0f;
    p->flags |= DEATH_MASK;
}

void powerupMultiActivate(Entity_T* p) {
    Entity_T* b1 = addBall(randomFloat(300, 600), app.SCREEN_HEIGHT / 2, 0);
    Entity_T* b2 = addBall(randomFloat(300, 600), app.SCREEN_HEIGHT / 2, 0);

    currentLevel->ballTail->next = b1;
    currentLevel->ballTail = b1;
    currentLevel->ballTail->next = b2;
    currentLevel->ballTail = b2;

    p->flags |= DEATH_MASK;
}

void powerupCoinActivate(Entity_T* p) {
    addScoreItem(p->x, p->y, COIN_SCORE);
    playSound(SND_COIN, CH_ANY);
    stage.score += COIN_SCORE;
    p->flags |= DEATH_MASK;
}

void powerupLifeActivate(Entity_T* p) {
    if (paddle->life <= MAX_LIVES) {
        paddle->life++;
    }
    addScoreItem(p->x, p->y, LIFE_SCORE);
    playSound(SND_EXTRA_LIFE, CH_ANY);
    stage.score += LIFE_SCORE;
    p->flags |= DEATH_MASK;
}
