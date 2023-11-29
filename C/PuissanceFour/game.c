#include <stdio.h>
#include <assert.h>

#include "init.h"
#include "grid.h"
#include "game.h"

bool insertValue(grid_t* grille, size_t idColumn, content_t value) {
    assert(grille);
    assert(idColumn < grille->columns);
    assert(value != EMPTY);

    if (grille->nextLine[idColumn] < 0)
        return false;

    grille->values[grille->nextLine[idColumn]][idColumn] = value;
    grille->nextLine[idColumn]++;

    return true;
}

bool isLoose(grid_t* grille) {
    assert(grille);

    for (size_t i = 0; i < grille->lines; i++) {
        for (size_t j = 0; j < grille->columns; j++) {
            if (grille->values[i][j] == EMPTY)
                return false;
        }
    }

    return true;
}


static inline bool isLineFull(grid_t* grille, int idLine, content_t value) {

    int acc = 0;
    for (size_t i = 0; i < grille->columns; i++) {
        if (grille->values[grille->lines - idLine - 1][i] != value) {
            acc = 0;
        }
        else {
            acc++;
        }

        if (acc == 4)
            return true;
    }

    return false;
}

static inline bool isColumnFull(grid_t* grille, int idColumn, content_t value) {

    int acc = 0;
    for (size_t i = 0; i < grille->lines; i++) {
        if (grille->values[i][idColumn] != value) {
            acc = 0;
        }
        else {
            acc++;
        }

        if (acc == 4)
            return true;
    }

    return false;
}

static inline bool isDiagonalFull(grid_t* grille, int idLine, int idColumn, content_t value) {
    if (idLine + 3 < (int)grille->lines) {
        if (idColumn + 3 < (int)grille->columns) {
            if (grille->values[idLine][idColumn] == value
                && grille->values[idLine + 1][idColumn + 1] == value
                && grille->values[idLine + 2][idColumn + 2] == value
                && grille->values[idLine + 3][idColumn + 3] == value) { return true; }
        }

        if (idColumn - 3 >= 0) {
            if (grille->values[idLine][idColumn] == value
                && grille->values[idLine + 1][idColumn - 1] == value
                && grille->values[idLine + 2][idColumn - 2] == value
                && grille->values[idLine + 3][idColumn - 3] == value) { return true; }
        }
    }

    return false;
}


bool isWin(grid_t* grille, content_t value) {
    assert(grille);
    assert(value != EMPTY);

    for (size_t i = 0; i < grille->lines; i++) {
        if (isLineFull(grille, i, value))
            return true;
    }

    for (size_t i = 0; i < grille->columns; i++) {
        if (isColumnFull(grille, i, value))
            return true;
    }

    for (int i = 0; i < (int)grille->lines; i++) {
        for (int j = 0; j < (int)grille->columns; j++) {
            if (isDiagonalFull(grille, i, j, value))
                return true;
        }
    }

    return false;
}

gstatus_t gameLoop(grid_t* grille, bool isJ1Playing, const char* nameJ1, const char* nameJ2) {
    assert(grille && nameJ1 && nameJ2);

    P4_CLEAR_CONSOLE;

    const char* name = isJ1Playing ? nameJ1 : nameJ2;
    const content_t c = isJ1Playing ? CIRCLE : CROSS;

    printGrid(grille);
    printf("\nIt's %s's turn : \n", name);

    int choice;
    do {
        P4_SCANF("%d", &choice, sizeof (int));
        choice--;
    }
    while (choice < 0 || choice >= (int)grille->columns);


    if (!insertValue(grille, (size_t)choice, c)) {
        P4_CLEAR_CONSOLE;
        printf("The column is already full...\n");
        P4_SLEEP(1500);
        return GAME_STATUS_NORMAL;
    }

    if (isLoose(grille))
        return GAME_STATUS_GAMEOVER;

    if (isWin(grille, c))
        return isJ1Playing ? GAME_STATUS_P1_WIN : GAME_STATUS_P2_WIN;

    return GAME_STATUS_NORMAL;
}


bool endGameScreen(gstatus_t status, const char* nameJ1, const char* nameJ2) {
    P4_CLEAR_CONSOLE;

    switch (status) {
        case GAME_STATUS_GAMEOVER:
            printf("The grid is full, That's a tie!\n");
            break;

        case GAME_STATUS_P1_WIN:
            printf("%s won the game !\n", nameJ1);
            break;

        case GAME_STATUS_P2_WIN:
            printf("%s won the game !\n", nameJ2);
            break;

        default:
            printf("Error !");
            P4_SLEEP(3000);
            return false;
    }

    printf("Do you want to play again? (y/n)");

    char choice[2];

    while (1) {
        P4_SCANF("%s", choice, 2 * sizeof (char));

        if (choice[1] == '\n' && (choice[0] == 'y' || choice[0] == 'Y'))
            return true;

        else if (choice[1] == '\n' && (choice[0] == 'n' || choice[0] == 'N'))
            return false;
    }
}
