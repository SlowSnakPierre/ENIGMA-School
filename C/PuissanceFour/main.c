#include <stdio.h>
#include <stddef.h>

#include "init.h"
#include "grid.h"
#include "game.h"

#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0 // LINUX PATCH
#endif

extern char *utf8_scanf(size_t);
extern void getDimensions(int, char**, int*, int*);

void printLogo() {
    printf(R"EOF(__________      .__                                               _____
\______   \__ __|__| ______ ___________    ____   ____  ____     /  |  |
 |     ___/  |  \  |/  ___//  ___/\__  \  /    \_/ ___\/ __ \   /   |  |_
 |    |   |  |  /  |\___ \ \___ \  / __ \|   |  \  \__\  ___/  /    ^   /
 |____|   |____/|__/____  >____  >(____  /___|  /\___  >___  > \____   |
                        \/     \/      \/     \/     \/    \/       |__| )EOF");
    printf("\n\n\n");
}

int main(int argc, char* argv[]) {
    int lines, columns;
    getDimensions(argc, argv, &lines, &columns);

    P4_INIT_CONSOLE;

    char *player1;
    char *player2;

    P4_CLEAR_CONSOLE;
    printLogo();
    printf("Entrez le nom du Joueur 1:\n");
    player1 = utf8_scanf(100);

    P4_CLEAR_CONSOLE;
    printLogo();
    printf("Entrez le nom du Joueur 2:\n");
    player2 = utf8_scanf(100);

    grid_t* grid;
    gstatus_t status;
    bool isP1Playing;

    while (true) {
        grid = makeGrid((size_t) lines, (size_t) columns);
        status = GAME_STATUS_NORMAL;
        isP1Playing = true;

        while (status == GAME_STATUS_NORMAL) {
            status = gameLoop(grid, isP1Playing, player1, player2);
            isP1Playing = !isP1Playing;
        }

        freeGrid(grid);

        if (!endGameScreen(status, player1, player2))
            break;
    }

    P4_RESET_CONSOLE;

    return EXIT_SUCCESS;
}