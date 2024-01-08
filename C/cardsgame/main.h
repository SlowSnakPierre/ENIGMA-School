#ifdef WIN32
    #define CLR system("cls");
#else
    #define CLR system("clear");
#endif

typedef struct Card {
    int value;
    int color;
    char name[5];
} Card;

typedef struct Element {
    struct Card* elem;
    struct Element* next;
} Element;

typedef struct Deck {
    struct Element* first;
} Deck;

void PrintDeck(Deck* deck);
int CountCardsScore(Deck* deck);
int CountCards(Deck* deck);
Card* pickCard(Deck* deck);
Deck* shuffleCard(Deck* deck);
Deck* SetupCardDraw(Deck* deck, int asScore);
Deck* CreateDeck();
Deck* InsertExistingCard(Card* card, Deck* deck);
Deck* InsertCard(int value, int color, char name[5], Deck* deck);
int checkBlackJack(Deck* deck);
void logo();