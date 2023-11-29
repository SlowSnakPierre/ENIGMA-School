#ifndef __grid_h__
#define __grid_h__

#include <stddef.h>
#include <stdbool.h>

typedef enum content_e {
    EMPTY = 0x0000,
    CIRCLE = 0x0001,
    CROSS = 0x0002
} content_t;

typedef struct grid_s {
    size_t lines;
    size_t columns;
    content_t** values;
    int* nextLine;
} grid_t;

grid_t* makeGrid(size_t, size_t);
void freeGrid(grid_t*);
void printGrid(grid_t*);

#endif