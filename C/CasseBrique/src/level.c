#include "../inc/level.h"

#define MAXC            16
#define CHAR_OFFSET     48
#define BRICK_ROW_COUNT 10
#define BRICK_COL_COUNT 6
#define BRICK_WIDTH     92
#define BRICK_HEIGHT    32

static Entity_T* spawnPowerup(const Entity_T*);

static void updateBalls(void);

static void updatePowerups(void);

static void updateBricks(void);

static void updateScoreItems(void);

static void drawBalls(void);

static void drawPowerups(void);

static void drawBricks(void);

static void drawScoreItems(void);

static void ballHitPaddle(Entity_T*);

static void ballHitBrick(Entity_T*);

static void powerupHitPaddle(Entity_T*);


Level_T* addLevel(const int level_id) {
    const int MAX_DIGITS = 3;

    char level_data[MAX_BUFFER_SIZE];
    char number_buffer[MAX_DIGITS];
    const char* file_extsn = ".txt";

    sprintf(number_buffer, "%d", level_id);
    strcpy(level_data, "res/level_data/level_");
    strcat(level_data, number_buffer);
    strcat(level_data, file_extsn);

    FILE* fptr = fopen(level_data, "r");
    print("Loading : %s", level_data);

    if (fptr == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not read from file! %s\n", SDL_GetError());
        exit(4);
    }

    Level_T* level = malloc(sizeof(Level_T));
    memset(level, 0, sizeof(Level_T));

    level->entityTail = &level->entityHead;
    level->ballTail = &level->ballHead;
    level->brickTail = &level->brickHead;
    level->powerupTail = &level->powerupHead;
    level->scoreItemTail = &level->scoreItemHead;
    level->brickCount = 0;


    for (int y = 120; y < 120 + BRICK_HEIGHT * BRICK_ROW_COUNT; y += 32) {
        char buffer[MAXC];
        fgets(buffer, MAXC, fptr);
        for (int x = 20, bi = 0; x <= app.SCREEN_WIDTH - 80; x += 92, bi++) {
            const int c = buffer[bi] - '\0' - CHAR_OFFSET;

            if (c < 0) {
                break;
            }

            if (c != 0) {
                Entity_T* b = addBrick(x, y, 0, c);

                level->brickTail->next = b;
                level->brickTail = b;
                level->brickCount++;
            }
        }
    }

    fclose(fptr);
    return level;
}

void updateLevel() {
    if (app.gameState != TRANSITION) {
        updateBalls();
        updatePowerups();
        updateScoreItems();
    }
    updateBricks();
}

void drawLevel() {
    drawBalls();
    drawPowerups();
    drawScoreItems();
    drawBricks();
}

void setNextLevel(void) {
    Level_T* l = addLevel(stage.levelId);
    loadLevelMusic(stage.levelId);
    stage.levelTail->next = l;
    stage.levelTail = l;
    currentLevel = l;
}

void removeLevel() {
    Level_T* l = stage.levelHead.next;
    while (l != NULL) {
        Level_T* tmp = l->next;
        free(l);
        l = tmp;
    }

    if (currentLevel != NULL) {
        free(currentLevel);
        currentLevel = NULL;
    }
}

void removeBalls(void) {
    Entity_T* b = &currentLevel->ballHead;

    while (b != NULL) {
        Entity_T* tmp = b->next;
        b = NULL;
        free(b);
        b = tmp;
    }
}

void loadLevelMusic(const int level) {
    loadMusic("res/sfx/music/ingame.ogg");
    playMusic(true);
}

static void updateBalls(void) {
    if (currentLevel->ballCount == 0 && app.gameState == RUNNING) {
        paddle->life--;
        activateTransition(true);
    }

    Entity_T* prevBall = &currentLevel->ballHead;

    for (Entity_T* b = currentLevel->ballHead.next; b != NULL; b = b->next) {
        if (b->idFlags & ID_BALL_MASK) {
            ballHitPaddle(b);
            ballHitBrick(b);
            ballUpdate(b);
        }

        if (b->flags & DEATH_MASK) {
            if (b == currentLevel->ballTail) {
                currentLevel->ballTail = prevBall;
            }

            prevBall->next = b->next;
            ballDestroy(b);
            b = prevBall;
            paddle->x = app.SCREEN_WIDTH / 2 - paddle->w / 2;
        }

        prevBall = b;
    }
}

static void updatePowerups(void) {
    Entity_T* prev = &currentLevel->powerupHead;

    for (Entity_T* p = currentLevel->powerupHead.next; p != NULL; p = p->next) {
        if (p->idFlags & ID_DEFAULT_POWERUP_MASK) {
            powerupHitPaddle(p);
            powerupUpdate(p);
        }

        if (p->flags & DEATH_MASK) {
            if (p == currentLevel->powerupTail) {
                currentLevel->powerupTail = prev;
            }

            prev->next = p->next;
            powerupDie(p);
            p = prev;
        }
        prev = p;
    }
}

static void updateBricks(void) {
    Entity_T* prevBrick = &currentLevel->brickHead;

    for (Entity_T* brick = currentLevel->brickHead.next; brick != NULL; brick = brick->next) {
        updateBrick(brick);

        if (brick->flags & DEATH_MASK) {
            if (brick == currentLevel->brickTail) {
                currentLevel->brickTail = prevBrick;
            }
            prevBrick->next = brick->next;
            removeBrick(brick);
            brick = prevBrick;
        }
        prevBrick = brick;
    }
}

static void updateScoreItems(void) {
    ScoreItem_T* prev = &currentLevel->scoreItemHead;

    for (ScoreItem_T* s = currentLevel->scoreItemHead.next; s != NULL; s = s->next) {
        updateScoreItem(s);

        if (s->flags & DEATH_MASK) {
            if (s == currentLevel->scoreItemTail) {
                currentLevel->scoreItemTail = prev;
            }

            prev->next = s->next;
            free(s);
            s = prev;
        }
        prev = s;
    }
}

static void drawPowerups(void) {
    Entity_T* p;

    for (p = currentLevel->powerupHead.next; p != NULL; p = p->next) {
        if (p->idFlags & ID_DEFAULT_POWERUP_MASK) {
            powerupDraw(p);
        }
    }
}

static void drawScoreItems(void) {
    for (const ScoreItem_T* s = currentLevel->scoreItemHead.next; s != NULL; s = s->next) {
        drawScoreItem(s);
    }
}

static void drawBalls(void) {
    for (const Entity_T* b = currentLevel->ballHead.next; b != NULL; b = b->next) {
        if (b->idFlags & ID_BALL_MASK) {
            ballDraw(b);
        }
    }
}

static void drawBricks(void) {
    for (const Entity_T* b = currentLevel->brickHead.next; b != NULL; b = b->next) {
        drawBrick(b);
    }
}

static void ballHitBrick(Entity_T* ball) {
    for (Entity_T* brick = currentLevel->brickHead.next; brick != NULL; brick = brick->next) {
        if (check_intersection((int)ball->x, (int)ball->y, ball->w, ball->h, (int)brick->x, (int)brick->y, brick->w,
                               brick->h)) {
            brick->life--;
            if (brick->life > 0) {
                playSound(SND_BRICK_SHATTER, CH_BRICK);
            }
            else {
                Entity_T* p = spawnPowerup(brick);

                if (p != NULL) {
                    currentLevel->powerupTail->next = p;
                    currentLevel->powerupTail = p;
                }

                currentLevel->brickCount--;
                currentLevel->lastBreakTimer++;

                playSound(SND_BRICK_BREAK, CH_BRICK);
                addScoreItem(brick->x + brick->w / 4, brick->y + brick->h / 4, 0);

                if (currentLevel->brickCount == 0) {
                    activateTransition(false);
                }
            }

            ball->dy = -ball->dy;
            addDebris(brick);
            break;
        }
    }
}

static void ballHitPaddle(Entity_T* b) {
    if (check_intersection((int)paddle->x, (int)paddle->y, paddle->w, paddle->h, (int)b->x, (int)b->y, b->w, b->h)) {
        const int SIZE = 16;
        const double rel = paddle->x + paddle->w / 2 - (b->x + SIZE / 2);
        const double norm = rel / (paddle->w / 2);
        const double bounce = norm * (5 * PI / 12);

        b->dx = (float)(BALL_SPEED_DEFAULT * -sin(bounce));
        b->dy = (float)(-BALL_SPEED_DEFAULT * cos(bounce));
    }
}

static void powerupHitPaddle(Entity_T* p) {
    if (check_intersection((int)paddle->x, (int)paddle->y, paddle->w, paddle->h, (int)p->x, (int)p->y, p->w, p->h) && p
        ->flags & POWERUP_INACTIVE) {
        if (p->identifier == LARGE_PADDLE) {
            powerupLargeActivate(p);
        }
        else if (p->identifier == MULTI_BALL) {
            powerupMultiActivate(p);
        }
        else if (p->identifier == GOLD_COIN) {
            powerupCoinActivate(p);
        }
        else if (p->identifier == EXTRA_LIFE) {
            powerupLifeActivate(p);
        }
    }
}

static Entity_T* spawnPowerup(const Entity_T* parent) {
    const float prob = randomFloat(1.0f, 1000.0f);

    if (prob < 50.0f) {
        return addPowerup(parent->x, parent->y, 0, EXTRA_LIFE);
    }

    if (prob < 100.0f) {
        return addPowerup(parent->x, parent->y, 0, LARGE_PADDLE);
    }

    if (prob < 150.0f) {
        return addPowerup(parent->x, parent->y, 0, MULTI_BALL);
    }

    if (prob < 500.0f) {
        return addPowerup(parent->x, parent->y, 0, GOLD_COIN);
    }

    return NULL;
}
