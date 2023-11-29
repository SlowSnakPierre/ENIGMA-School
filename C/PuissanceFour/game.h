#ifndef __game_h__
#define __game_h__

#include <stddef.h>
#include <stdbool.h>

#include "grid.h"

typedef enum game_status_e {
    GAME_STATUS_NORMAL = 0x0000,
    GAME_STATUS_GAMEOVER = 0xFFFF,
    GAME_STATUS_P1_WIN = 0x0001,
    GAME_STATUS_P2_WIN = 0x0002,
} gstatus_t;

gstatus_t gameLoop(grid_t *, bool, const char*, const char*);
bool endGameScreen(gstatus_t, const char*, const char*);
bool insertValue(grid_t *, size_t, content_t);
bool isWin(grid_t *, content_t);
bool isLoose(grid_t *);

#endif