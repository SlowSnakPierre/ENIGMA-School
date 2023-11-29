#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "init.h"
#include "grid.h"


grid_t* makeGrid(size_t lines, size_t columns)
{
    assert(lines != 0 && columns != 0);
    assert(lines >= 4 && columns >= 4);

    grid_t* grille = (grid_t*)(malloc(sizeof (grid_t)));

    grille->lines = lines;
    grille->columns = columns;

    grille->values = (content_t**)(malloc(lines * sizeof (grid_t*)));
    for (size_t i = 0; i < grille->lines; i++) {
        grille->values[i] = (content_t*)(malloc(columns * sizeof (content_t)));

        for (size_t j = 0; j < columns; j++) {
            grille->values[i][j] = EMPTY;
        }
    }

    grille->nextLine = (int*)(malloc(columns * sizeof (int)));
    for (size_t i = 0; i < grille->columns; i++) {
        grille->nextLine[i] = (int)(lines-1);
    }

    return grille;
}

void freeGrid(grid_t* grille)
{
    if (!grille)
        return;

    if (grille->nextLine)
        free(grille->nextLine);

    if (grille->values) {
        for (size_t i = 0; i < grille->lines; i++) {
            if (grille->values[i])
                free(grille->values[i]);
        }
        free(grille->values);
    }

    free(grille);
}


void printGrid(grid_t* grille)
{
    P4_CLEAR_CONSOLE;

    const size_t lsep_l = (grille->columns+1) * P4_DEFAULT_WIDTH;
    char* lsep = (char*)(malloc(lsep_l * sizeof (char)));
    for (size_t i = 0; i < lsep_l; i++) {
        lsep[i] = '.';
    }
    lsep[lsep_l] = '\0';

    printf("%s\n", lsep);

    for (size_t i = 0; i < grille->lines; i++) {
        for (size_t j = 0; j < grille->columns; j++) {
            printf("|");

            for (size_t k = 0; k < (P4_DEFAULT_WIDTH)/2; k++) {
                printf(" ");
            }

            switch (grille->values[i][j]) {
            case CIRCLE:
                printf("O");
                break;

            case CROSS:
                printf("X");
                break;

            default:
                printf(" ");
                break;
            }

            for (size_t k = 0; k < (P4_DEFAULT_WIDTH)/2; k++) {
                printf(" ");
            }
        }

        printf("|\n%s\n", lsep);
    }

    for (size_t i = 0; i < grille->columns; i++) {
        for (size_t j = 0; j < (P4_DEFAULT_WIDTH+1)/2; j++) {
            printf(" ");
        }
        printf("%zu", i+1);
        for (size_t j = 0; j < (P4_DEFAULT_WIDTH)/2; j++) {
            printf(" ");
        }
    }

    printf("\n");
    free(lsep);
}