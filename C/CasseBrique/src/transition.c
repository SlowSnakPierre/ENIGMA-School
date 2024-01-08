#include "../inc/transition.h"

#define MUSIC_FADE           3000
#define TRANSITION_LIFE_MULT 10
#define MAX_ALPHA            255

static int life;
static int alpha;
static bool is_restart;

static SDL_Rect r;

void activateTransition(const bool restart) {
    is_restart = restart;
    r.x = r.y = 0;
    r.w = app.SCREEN_WIDTH;
    r.h = app.SCREEN_HEIGHT;

    if (app.gameState != TRANSITION) {
        Mix_FadeOutMusic(MUSIC_FADE);
        app.gameState = TRANSITION;
        life = FPS * TRANSITION_LIFE_MULT;
        alpha = 0;
    }
}

void updateTransition(void) {
    if (alpha < MAX_ALPHA) {
        alpha++;
    }
    else {
        removeBalls();
    }

    if (--life <= 0) {
        app.gameState = PREGAME;

        if (!is_restart) {
            stage.levelId++;
        }
        setNextLevel();
    }
}

void drawTransition(void) {
    SDL_Color c;
    c.r = c.g = c.b = 0;
    c.a = alpha;
    drawRect(&r, &c, true, false);
}
