#ifndef GAME_DEFS_H
#define GAME_DEFS_H

#include "commons.h"

#define MAX_DEBRIS_IMGS             3

#define BALL_DEATH_PARTICLES 20
#define BALL_SPEED_DEFAULT 10.0f

#define ID_BALL_MASK                0x00000001
#define POWERUP_ACTIVE              0x00200000
#define POWERUP_INACTIVE            0x00400000
#define ID_DEFAULT_POWERUP_MASK     0x00100000
#define ID_DEFAULT_BRICK_MASK       0x00001000
#define ID_PLAYER_MASK              0x00002000
#define ID_PARTICLE_MASK            0x00004000
#define ID_P_SQUARE_MASK            0x00008000
#define ID_P_CIRCLE_MASK            0x00010000
#define ID_P_STAR_MASK              0x00000200

enum Powerup { MULTI_BALL, LARGE_PADDLE, EXTRA_LIFE, GOLD_COIN };

enum Brick {
    NULL_COLOR,
    RED,
    BLUE,
    BROWN,
    YELLOW,
    ORANGE,
    PURPLE,
    DARK_GREEN,
    LIGHT_GREEN,
    LIGHT_BLUE,
};

#endif