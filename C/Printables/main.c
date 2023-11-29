#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int nombreHypotetique = 0, nombreMystere = 0, compteur = 0, choixMenu = 1;
    const int MAX = 100, MIN = 1;
    srand (time(NULL));

    printf("\n\n\n            === Bienvenue dans le jeu du juste prix ===  ");
    while ( choixMenu == 1 ) {
        compteur=0;
        nombreMystere = (rand() % (MAX - MIN + 1)) + MIN;

        printf("\n\n\n");
        printf("Voulez vous jouer au juste prix ?\n\n");
        printf("1. Oui\n\n");
        printf("2. Non\n\n");
        scanf("%d", &choixMenu);
        switch ( choixMenu ) {
            case 1:
                do {
                    printf("\n\ntrouvez le juste prix entre 1 et 100  :  ");
                    scanf("%d", &nombreHypotetique);
                    printf("\n\n");
                    compteur++;

                    if (nombreMystere < nombreHypotetique)
                        printf("c'est moins\n\n");
                    else if (nombreMystere > nombreHypotetique)
                        printf("c'est plus\n\n");
                    else
                        printf("vous avez trouve le juste prix en %d coups\n\n", compteur);
                } while (nombreHypotetique != nombreMystere);
            break;
        }
    }

    return 0;
}