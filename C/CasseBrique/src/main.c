#include "../inc/main.h"

#define S_WIDTH 775
#define S_HEIGHT 960
#define L_WIDTH 0
#define L_HEIGHT 0

bool debounce = false;

static void initScene(void);

static void draw(void);

static void tick(void);

static void checkPregame(void);

static void checkPaused(void);

static void checkTransition(void);

static void cleanupStage(void);

static void updateEntities(void);

static void updateAllDebris(void);

static void updateTrails(void);

static void drawEntities(void);

static void drawAllDebris(void);

static void drawTrails(void);

ParticleSystem_T* ps;
Stage_T stage;
Entity_T* paddle;
Background_T* background;
Level_T* currentLevel;
App_T app;

int main(int argc, char* argv[]) {
    initGame("Casse-Brique", S_WIDTH, S_HEIGHT, L_WIDTH, L_HEIGHT);
    initAppStructures();
    initScene();
    initMenu();
    loop();

    atexit(cleanupStage);
    return 0;
}

static void initScene(void) {
    app.delegate.tick = tick;
    app.delegate.draw = draw;
    app.gameState = PREGAME;

    memset(&stage, 0, sizeof(Stage_T));
    stage.levelTail = &stage.levelHead;
    stage.debrisTail = &stage.debrisHead;
    stage.state = MENU;
    stage.levelId = 1;

    Level_T* level = addLevel(stage.levelId);
    stage.levelTail->next = level;
    stage.levelTail = level;
    currentLevel = stage.levelTail;
    background = initBackground("res/img/background/bg.png");

    initPaddle();
    initHUD();

    ps = createParticleSystem(51222);
}

static void tick(void) {
    if (app.keyboard[SDL_SCANCODE_ESCAPE] && !debounce) {
        app.gameState = app.gameState == PAUSED ? 0 : PAUSED;
        debounce = true;
    } else if (!app.keyboard[SDL_SCANCODE_ESCAPE] && debounce) {
        debounce = false;
    }

    checkPregame();
    checkTransition();
    checkPaused();
    checkTransition();

    if (app.gameState == PAUSED) {
        return;
    }

    updateHUD();

    if (stage.state == GAME) {
        updateParticleSystem(ps);
        updateEntities();
        updateTrails();
        updateAllDebris();
        updateLevel();
    }

    if (app.gameState != TRANSITION) {
        updatePaddle();
    }
}

static void draw(void) {
    backgroundDraw(background);
    if (stage.state == GAME) {
        drawParticleSystem(ps);
        drawEntities();
        drawTrails();
        drawAllDebris();
        drawLevel();
        drawPaddle();
    }

    if (app.gameState == TRANSITION) {
        drawTransition();
    }
    drawHUD();

    if (app.gameState == PAUSED) {
        pausedHUD();
    }
}

static void updateEntities(void) {
    Entity_T* prev = &currentLevel->entityHead;

    for (Entity_T* e = currentLevel->entityHead.next; e != NULL; e = e->next) {
        if (e->tick) {
            e->tick(e);
        }

        if (e->flags & DEATH_MASK) {
            if (e == currentLevel->entityTail) {
                currentLevel->entityTail = prev;
            }

            prev->next = e->next;
            free(e);
            e = prev;
        }
        prev = e;
    }
}

static void updateAllDebris(void) {
    Debris_T* prev = &stage.debrisHead;

    for (Debris_T* d = stage.debrisHead.next; d != NULL; d = d->next) {
        updateDebris(d);

        if (d->flags & DEATH_MASK) {
            if (d == stage.debrisTail) {
                stage.debrisTail = prev;
            }

            prev->next = d->next;
            removeDebris(d);
            d = prev;
        }
        prev = d;
    }
}

static void updateTrails(void) {
    Trail_T* prev = &app.trailHead;

    for (Trail_T* t = app.trailHead.next; t != NULL; t = t->next) {
        updateTrail(t);

        if (t->flags & DEATH_MASK) {
            if (t == app.trailTail) {
                app.trailTail = prev;
            }

            prev->next = t->next;
            free(t);
            t = prev;
        }
        prev = t;
    }
}

static void drawEntities(void) {
    for (Entity_T* e = currentLevel->entityHead.next; e != NULL; e = e->next) {
        if (e->draw) {
            e->draw(e);
        }
    }
}

static void drawAllDebris(void) {
    for (const Debris_T* d = stage.debrisHead.next; d != NULL; d = d->next) {
        drawDebris(d);
    }
}

static void drawTrails(void) {
    for (const Trail_T* t = app.trailHead.next; t != NULL; t = t->next) {
        drawTrail(t);
    }
}

static void checkPaused(void) {
    if (app.keyboard[SDL_SCANCODE_P] && stage.state == GAME) {
        app.gameState = app.gameState == PAUSED ? RUNNING : PAUSED;
        app.keyboard[SDL_SCANCODE_P] = 0;
    }

    if (app.gameState == PAUSED) {
        Mix_PauseMusic();
    }
    else {
        Mix_ResumeMusic();
    }
}

static void checkTransition(void) {
    if (app.gameState == TRANSITION) {
        updateTransition();
    }
}

static void checkPregame(void) {
    if (app.keyboard[SDL_SCANCODE_SPACE] && app.gameState == PREGAME) {
        app.keyboard[SDL_SCANCODE_SPACE] = 0;
        Entity_T* b = addBall(app.SCREEN_WIDTH / 2, (app.SCREEN_HEIGHT / 3)*2, 0);
        currentLevel->ballTail->next = b;
        currentLevel->ballTail = b;
        app.gameState = RUNNING;
    }
}

static void cleanupStage(void) {
    for (Level_T* l = stage.levelHead.next; l != NULL; l = l->next) {
        while (l->ballHead.next) {
            Entity_T* ball = l->ballHead.next;
            l->ballHead.next = ball->next;
            free(ball);
        }

        while (l->brickHead.next) {
            Entity_T* brick = l->brickHead.next;
            l->brickHead.next = brick->next;
            free(brick);
        }

        while (l->entityHead.next) {
            Entity_T* en = l->entityHead.next;
            l->entityHead.next = en->next;
            free(en);
        }
    }

    while (stage.animationHead.next) {
        Animation_T* a = stage.animationHead.next;
        stage.animationHead.next = a->next;
        free(a);
    }

    free(currentLevel);
    removePaddle();
    backgroundDie(background);
    free(ps->particles);
    free(ps);
}
