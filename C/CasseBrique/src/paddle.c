#include "../inc/paddle.h"

#define PADDLE_H_VELOCITY   10.0f
#define PADDLE_DECELERATION 0.85f

static void keyInputUpdate(void);

static void checkBounds(void);

void initPaddle(void) {
    paddle = malloc(sizeof(Entity_T));
    memset(paddle, 0, sizeof(Entity_T));

    paddle->life = 5;
    paddle->texture[0] = loadTexture("res/img/paddle.png");
    SDL_QueryTexture(paddle->texture[0], NULL, NULL, &paddle->w, &paddle->h);

    paddle->x = app.SCREEN_WIDTH / 2 - paddle->w / 2;
    paddle->y = app.SCREEN_HEIGHT - 40;
    paddle->scaleX = 1.0f;
    paddle->scaleY = 1.0f;
    paddle->idFlags |= ID_PLAYER_MASK;
}

void updatePaddle(void) {
    paddle->x += paddle->dx;
    paddle->y += paddle->dy;

    checkBounds();
    keyInputUpdate();
}

void drawPaddle(void) {
    blitTextureScaled(paddle->texture[0], paddle->x, paddle->y, paddle->scaleX, paddle->scaleY,
                      paddle->angle, SDL_FLIP_NONE, false);
}

void removePaddle(void) {
    free(paddle);
}

static void checkBounds(void) {
    if (paddle->x < 0) {
        paddle->x = 0;
    }
    else if (paddle->x + paddle->w > app.SCREEN_WIDTH) {
        paddle->x = app.SCREEN_WIDTH - paddle->w;
    }
    else if (paddle->y < 0) {
        paddle->y = 0;
    }
    else if (paddle->y + paddle->h > app.SCREEN_HEIGHT) {
        paddle->y = app.SCREEN_HEIGHT - paddle->h;
    }
}

static void keyInputUpdate(void) {
    if (app.gameState != PAUSED) {
        paddle->dx *= PADDLE_DECELERATION;
        paddle->dy *= PADDLE_DECELERATION;

        if (app.keyboard[SDL_SCANCODE_A] || app.keyboard[SDL_SCANCODE_LEFT]) {
            paddle->dx = -PADDLE_H_VELOCITY;
        }

        if (app.keyboard[SDL_SCANCODE_D] || app.keyboard[SDL_SCANCODE_RIGHT]) {
            paddle->dx = PADDLE_H_VELOCITY;
        }
    }
}
