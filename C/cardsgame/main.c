#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "ansi.h"
#include "main.h"

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * x)
#else
    #include <unistd.h>
#endif

Deck* InsertCard(int value, int color, char name[5], Deck* deck) {
    Element* newElement = (Element*)malloc(sizeof(Element));
    Card* newCard = (Card*)malloc(sizeof(Card));
    newCard->value = value;
    newCard->color = color;
    strcpy(newCard->name, name);
    newElement->elem = newCard;
    newElement->next = deck->first;
    deck->first = newElement;
    return deck;
}

Deck* InsertExistingCard(Card* card, Deck* deck) {
    Element* newElement = (Element*)malloc(sizeof(Element));
    newElement->elem = card;
    newElement->next = deck->first;
    deck->first = newElement;
    return deck;
}

Deck* CreateDeck() {
    Deck* deck = (Deck*)malloc(sizeof(Deck));
    deck->first = NULL;
    return deck;
}

Deck* SetupCardDraw(Deck* deck, int asScore) {
    for (int color = 0; color < 4; color++) {
        deck = InsertCard(asScore, color, "A", deck);
        for (int value = 2; value < 11; value++) {
            char name[5];
            sprintf(name, "%d", value);
            deck = InsertCard(value, color, name, deck);
        }
        deck = InsertCard(10, color, "V", deck);
        deck = InsertCard(10, color, "D", deck);
        deck = InsertCard(10, color, "R", deck);

    }
    return deck;
}

Deck* shuffleCard(Deck* deck) {
    srand(time(NULL));
    int count = CountCards(deck);
    Card** cards = (Card**)malloc(count * sizeof(Card*));
    int i = 0;

    Element* current = deck->first;
    while (current != NULL) {
        cards[i++] = current->elem;
        current = current->next;
    }

    for (int j = count - 1; j > 0; j--) {
        int k = rand() % (j + 1);
        Card* temp = cards[j];
        cards[j] = cards[k];
        cards[k] = temp;
    }

    current = deck->first;
    i = 0;
    while (current != NULL) {
        current->elem = cards[i++];
        current = current->next;
    }

    free(cards);
    return deck;
}

Card* pickCard(Deck* deck) {
    Element* current = deck->first;
    deck->first = deck->first->next;
    char colorName[15];

    switch (current->elem->color) {
        case 0:
            strcpy(colorName, "\x05 Trefle");
            printf(BHWHT);
            break;
        case 1:
            strcpy(colorName, "\x04 Carreau");
            printf(BHRED);
            break;
        case 2:
            strcpy(colorName, "\x03 Coeur");
            printf(BHRED);
            break;
        case 3:
            strcpy(colorName, "\x06 Pique");
            printf(BHWHT);
            break;
        default:
            break;
    }

    // printf("+ %s/ %s\n\n", current->elem->name, colorName);
    printf(CRESET);
    return current->elem;
}

int CountCards(Deck* deck) {
    int count = 0;
    Element* current = deck->first;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int CountCardsScore(Deck* deck) {
    int count = 0;
    Element* current = deck->first;

    while (current != NULL) {
        count += current->elem->value;
        current = current->next;
    }

    return count;
}

void PrintDeck(Deck* deck) {
    Element* current = deck->first;
    int t = 0;
    while (current != NULL) {
        char colorName[10];
        switch (current->elem->color) {
            case 0:
                strcpy(colorName, "\x05 Trefle");
                printf(BHWHT);
                break;
            case 1:
                strcpy(colorName, "\x04 Carreau");
                printf(BHRED);
                break;
            case 2:
                strcpy(colorName, "\x03 Coeur");
                printf(BHRED);
                break;
            case 3:
                strcpy(colorName, "\x06 Pique");
                printf(BHWHT);
                break;
            default:
                break;
        }

        if (t == 0)
            printf("-> ");
        printf("%s/ %s\n", current->elem->name, colorName);
        printf(CRESET);
        current = current->next;
        t++;
    }
    printf("\n");
}

int checkBlackJack(Deck* deck) {
    Element* current = deck->first;
    int asFound = 0;
    int bucheFound = 0;

    while (current != NULL) {
        if (current->elem->name == "A") // As
            asFound = 1;
        if (current->elem->value == 10) // Buche
            bucheFound = 1;
        current = current->next;
    }

    if (asFound == 1 && bucheFound == 1) return 1; // As + Buche = BlackJack
    return 0;
}

void logo() {
    printf(BHBLU);
    printf(R"EOF(
__________.__                 __        ____.              __
\______   \  | _____    ____ |  | __   |    |____    ____ |  | __
 |    |  _/  | \__  \ _/ ___\|  |/ /   |    \__  \ _/ ___\|  |/ /
 |    |   \  |__/ __ \\  \___|    </\__|    |/ __ \\  \___|    <
 |______  /____(____  /\___  >__|_ \________(____  /\___  >__|_ \
        \/          \/     \/     \/             \/     \/     \/

)EOF");
    printf(CRESET);
}

int main() {
    int cash = 25;
    int vague = 0;

    CLR;

    do {
        int asScore;
        int bet = 0;
        int turn = 0;

        int bankStatus = 0;
        int playerStatus = 0;

        Deck* playerDeck = CreateDeck();
        Deck* bankDeck = CreateDeck();
        Deck* cardDraw = CreateDeck();

        // Le joueur choisis sa mise
        do {
            logo();
            printf("Argent : %d eur\n", cash);
            printf("Mise (min 5) : ");

            scanf("%d", &bet);
            CLR;
        } while (bet < 5 || bet > cash);

        cash -= bet;


        // Joueur choisis combien vaut l'as
        do {
            logo();
            printf("Combien de points vaut l'As ? (1 ou 11)\n");
            scanf("%d", &asScore);
            CLR;
        } while (asScore != 1 && asScore != 11);

        // On mélange la pioche
        SetupCardDraw(cardDraw, asScore);
        shuffleCard(cardDraw);

        // Le joueur prend deux carte
        Card* playerCard = pickCard(cardDraw);
        InsertExistingCard(playerCard, playerDeck);

        playerCard = pickCard(cardDraw);
        InsertExistingCard(playerCard, playerDeck);

        // La banque prend une carte
        Card* bankCard = pickCard(cardDraw);
        InsertExistingCard(bankCard, bankDeck);

        do {
            logo();

            if ((CountCards(playerDeck) && checkBlackJack(playerDeck)) || (CountCards(bankDeck) && checkBlackJack(bankDeck))) {
                CLR;
                // J'affiche les decks
                printf(BHBLU);
                printf("\xaf Deck de la bank (Score : %d) \xae\n", CountCardsScore(bankDeck));
                printf(CRESET);
                PrintDeck(bankDeck);

                printf(BHBLU);
                printf("\xaf Mon Deck (Score : %d) \xae\n", CountCardsScore(playerDeck));
                printf(CRESET);
                PrintDeck(playerDeck);

                printf(BHYEL);
                printf("BlackJack !\n");
                printf(CRESET);

                if (turn == 0)
                    playerStatus = 3;
                else
                    bankStatus = 3;

                sleep(2);
                CLR;
            }

            if ((turn == 0 && playerStatus == 0) || (turn == 1 && bankStatus == 0)) {
                // Si c'est le joueur
                if (turn == 0) {
                    // J'affiche les decks
                    printf(BHBLU);
                    printf("\xaf Deck de la bank (Score : %d) \xae\n", CountCardsScore(bankDeck));
                    printf(CRESET);
                    PrintDeck(bankDeck);

                    printf(BHBLU);
                    printf("\xaf Mon Deck (Score : %d) \xae\n", CountCardsScore(playerDeck));
                    printf(CRESET);
                    PrintDeck(playerDeck);

                    // Je choisis l'action
                    int choice;
                    do {
                        printf(BHBLU);
                        printf("Que souhaitez vous faire ?\n");
                        printf(BHGRN);
                        printf("1/ Tirer une carte\n");
                        printf(BHRED);
                        printf("2/ Se coucher\n");
                        printf(CRESET);
                        scanf("%d", &choice);
                    } while (choice != 1 && choice != 2);

                    // Si j'ai choisis de me coucher je change de status
                    if (choice == 2) {
                        if (turn == 0)
                            playerStatus = 1;
                        else
                            bankStatus = 1;
                    }
                } else {
                    // Sinon si j'ai plus que 17 et que je suis toujours en course, je me couche
                    if (CountCardsScore(bankDeck) > 17 && bankStatus == 0)
                        bankStatus = 1;
                }
            }

            // Si je suis toujours en course je pioche une carte et je réaffiche les decks avec un clear
            if ((turn == 0 && playerStatus == 0) || (turn == 1 && bankStatus == 0)) {
                CLR;

                logo();

                Card* card = pickCard(cardDraw);
                InsertExistingCard(card, turn == 0 ? playerDeck : bankDeck);

                printf(BHBLU);
                printf("\xaf Deck de la bank (Score : %d) \xae\n", CountCardsScore(bankDeck));
                printf(CRESET);
                PrintDeck(bankDeck);

                printf(BHBLU);
                printf("\xaf Mon Deck (Score : %d) \xae\n", CountCardsScore(playerDeck));
                printf(CRESET);
                PrintDeck(playerDeck);
            }

            // Si j'ai plus que 21 je perds
            if (CountCardsScore(turn == 0 ? playerDeck : bankDeck) > 21) {
                if (turn == 0)
                    playerStatus = 2;
                else
                    bankStatus = 2;

                // Je casse ma boucle
                break;
            }

            // Si on est tous couché on casse la boucle
            if (playerStatus != 0 && bankStatus != 0)
                break;

            // Si un de nous est mort on casse la boucle
            if (playerStatus == 2 || bankStatus == 2)
                break;

            // Si c'était le tour de la banque, j'attend un peut avant de continuer
            if (turn == 1)
                sleep(2);

            CLR;

            turn = (turn + 1) % 2;

            // Temps que personne a un blackjack, on rejoue
        } while (playerStatus != 3 && bankStatus != 3);

        if (
            (bankStatus != 3) && (
            (playerStatus == 1 && bankStatus == 2) || // Le joueur s'est couché et la bank a perdu
            (playerStatus == 0 && bankStatus == 2) || // Le joueur est en jeu mais la bank a perdu
            (playerStatus == 3 && bankStatus != 3) || // Seul le joueur a un blackjack
            (playerStatus == 1 && bankStatus == 1 && CountCardsScore(playerDeck) > CountCardsScore(bankDeck)) // Les deux se sont couché mais le joueur a plus de points
            )
            ) { // Gagné

            if (playerStatus == 3) { // Si blackjack => x3 la mise
                bet = bet * 3;
            } else { // Sinon x2 la mise
                bet = bet * 2;
            }

            printf(BHGRN);
            printf("Gagne !\n");
            printf("+ %d eur", bet);
            printf(CRESET);
            cash += bet;

        } else if (
            (bankStatus == 3 && playerStatus == 3) || // Les deux ont un blackjack
            (playerStatus == 1 && bankStatus == 1 && CountCardsScore(playerDeck) == CountCardsScore(bankDeck)) // Les deux se sont couché mais égalité des points
            ) {

            printf(BHYEL);
            printf("Match nul !\n");
            printf("+ %d eur", bet);
            printf(CRESET);
            cash += bet;

        } else { // Perdu

            printf(BHRED);
            printf("Perdu !\n");
            printf("- %d eur", bet);
            printf(CRESET);

        }

        sleep(2);

        CLR;

        int output;
        printf("Argent : %d eur\n\n", cash);
        printf("Voulez vous rejouer ?\n1/ Oui \t\t 2/ Non\n");
        scanf("%d", &output);
        if (output == 2) break;
        CLR;
    } while (cash > 0);

    printf("Score final : %d eur\n", cash);

    return 0;
}