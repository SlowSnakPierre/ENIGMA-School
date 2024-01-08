#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "commons.h"
#include "game_defs.h"

typedef struct Stage Stage_T;
typedef struct Level Level_T;
typedef struct Debris Debris_T;
typedef struct ScoreItem ScoreItem_T;

typedef enum BrickBreakerState {
    MENU,
    GAME
} BrickBreakerState;

struct ScoreItem {
    float x;
    float y;
    char text[16];
    int score;
    int life;
    int flags;

    ScoreItem_T *next;
};

struct Level {
    size_t brickCount;
    size_t ballCount;
    int lastBreakTimer;

    Entity_T ballHead, *ballTail;
    Entity_T brickHead, *brickTail;
    Entity_T powerupHead, *powerupTail;
    Entity_T entityHead, *entityTail;
    ScoreItem_T scoreItemHead, *scoreItemTail;

    Background_T background;

    Level_T *next;
};

struct Debris {
    float x;
    float y;
    float dx;
    float dy;
    int flags;
    SDL_Texture *texture;
    SDL_Rect rect;

    Debris_T *next;
};

struct Stage {
    int score;
    int levelId;

    BrickBreakerState state;

    Animation_T animationHead, *animationTail;
    Level_T levelHead, *levelTail;
    Debris_T debrisHead, *debrisTail;
};

#endif