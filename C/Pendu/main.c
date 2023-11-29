#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include "dico.h"

// Seting up clear function for windows and linux + debugger
#if DEBUG
    #define CLR printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
#else
    #ifndef WIN32
        #define CLR system("cls");
    #else
        #define CLR system("clear");
    #endif
#endif

/**
 * @brief Draw the logo of the game
 */
void drawLogo() {
    printf(R"EOF(
__________.______________ ___________   _______________ _______   ____ ______________
\______   \   \_   _____/ \      \   \ /   /\_   _____/ \      \ |    |   \_   _____/
 |    |  _/   ||    __)_  /   |   \   Y   /  |    __)_  /   |   \|    |   /|    __)_
 |    |   \   ||        \/    |    \     /   |        \/    |    \    |  / |        \
 |______  /___/_______  /\____|__  /\___/   /_______  /\____|__  /______/ /_______  /
        \/            \/         \/                 \/         \/                 \/
                _____________________ _______  ________   ____ ___
                \______   \_   _____/ \      \ \______ \ |    |   \
        ______   |     ___/|    __)_  /   |   \ |    |  \|    |   /   ______
       /_____/   |    |    |        \/    |    \|    `   \    |  /   /_____/
                 |____|   /_______  /\____|__  /_______  /______/
                                  \/         \/        \/
)EOF");
}

/**
 * @brief Print the rules of the game
 */
void printRules() {
    printf(R"EOF(
1- Un nombre de "_" equivalent au nombre de lettres du mot vous apparait.
2- Vous devez deviner le mot en entrant les lettres du mot.
3- Vous avez 5 essais.
4- Si vous vous trompez de lettre, le systeme dessinera un morceau du bonhomme et vous perdrez un essai.
5- Vous perdez si le dessin du bonhomme est termine, ce qui signifie que le bonhomme est pendu !

La partie commence dans 15 secondes...
)EOF");
    sleep(15);
    CLR;
}

int main() {
    char yes_no[5];
    char yes[5] = "oui";
    int a = 1;
    int quit = 1;

    drawLogo();
    sleep(2);
    CLR;

    printf("Savez-vous jouer au pendu ? [oui/non]\n");
    scanf("%s", yes_no);
    CLR;

    if (strcmp(yes_no, yes) != 0)
        printRules();

    while (quit != 0) {
        char* word = getRandomWord();
        int letters = strlen(word);

        printf("Essayez de deviner le mot en devinant les lettres : \n\n");

        char answer[100];
        char wanswer[100] = " ";

        strcpy(answer, "");

        for (int i = 1; i <= letters; i++) {
            strcat(answer, "_ ");
            printf("_ ");
        }

        int b = 0;
        int c = 0;
        int p = 1;
        int finish = 0;

        while (c < 5) {
            printf("\n\nEntrez une lettre : \n");
            char letter;
            scanf("%s", &letter);
            CLR;
            if (strchr(word, letter) != 0) {
                for (int j = 0; j <= letters - 1; j++) {
                    if (letter == word[j]) {
                        p = j * 2;
                        if (answer[p] != letter) finish++;
                        answer[p] = letter;
                    }
                }

                printf("%s\n\n", answer);
                printf("Bonne reponse !\n");
                if (finish == letters) {
                    break;
                    b = 0;
                }
                if (b != 0)
                    printf("Lettres utilisees : %s", wanswer);
                if (c > 0)
                    c--;
            } else {
                wanswer[2 * b] = letter;
                strcat(wanswer, " ");
                b++;
                CLR;
                c++;
                if (c == 1)
                    printf(R"EOF(
o-----------
|          |
|
|
|
|
|
|___________
)EOF");
                if (c == 2)
                    printf(R"EOF(
o-----------
|          |
|          O
|
|
|
|
|___________
)EOF");
                if (c == 3)
                    printf(R"EOF(
o-----------
|          |
|          O
|          |
|          |
|
|
|___________
)EOF");
                if (c == 4)
                    printf(R"EOF(
o-----------
|          |
|          O
|          |
|          |
|         / \
|
|___________
)EOF");
                if (c == 5) {
                    CLR;
                    printf(R"EOF(
o-----------
|          |
|          O
|         \|/
|          |
|         / \
|
|___________
)EOF");
                }
                if (c != 5) {
                    printf("\n%d essais restant !\n\n", 4 - c);
                    printf("%s\n\n", answer);
                    printf("Lettres utilises: %s", wanswer);
                }
            }
        }

        if (finish == letters) {
            CLR;
            printf("C'est incroyable ! Vous avez gagne ! Le mot etait \"%s\" \n\n", word);
        }
        else {
            printf("Vous avez perdu ! Le mot etait \"%s\" \n\n", word);
        }
        printf("Vous voulez rejouer ou quitter ?\n1/ Rejouer 0/ Quitter\n");
        scanf("%d", &quit);
        CLR;
    }

    return 0;
}