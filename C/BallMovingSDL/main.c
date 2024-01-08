#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define MOVEMENT_DELAY 10
#define MAX_ENEMIES 25
#define MIN_ENEMIES 10
#define ENEMY_SIZE 0.2
#define PLAYER_SIZE 0.5
#define SPAWN_DELAY 200
#define COUNTDOWN_DURATION 3000
#define SCORE_DELAY 500

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
SDL_Texture* textureAsteroid;
SDL_Texture* texturePlayer;
SDL_Texture* textureHeart;
SDL_Texture* textureBackground;
SDL_Texture* textureMainMenuBackground;
TTF_Font* fontSmall;
TTF_Font* fontMed;
TTF_Font* fontBig;

typedef struct Enemy {
    SDL_Rect rect;
    int dx;
    int dy;
    bool active;
} Enemy;

typedef struct Player {
    SDL_Rect rect;
    int health;
    bool immune;
    Uint32 immuneStartTime;
} Player;

typedef struct Game {
    bool started;
    int score;
} Game;

typedef struct Button {
    SDL_Rect rect;
    SDL_Texture *texture;

    struct {
        Uint8 r, g, b;
    } hoveredColor;

    bool isPressed;
    bool isHovered;
} Button;

void btnProcessEvent(Button* btn, const SDL_Event event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (SDL_PointInRect(&(SDL_Point){event.button.x, event.button.y}, &btn->rect)) {
                    btn->isPressed = true;
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (SDL_PointInRect(&(SDL_Point){event.motion.x, event.motion.y}, &btn->rect)) {
                    btn->isHovered = true;
                } else {
                    btn->isHovered = false;
                }
            break;
        default:
            break;
    }
}

bool renderButton(SDL_Renderer* renderer, Button* btn) {
    if (btn->isPressed) {
        btn->isPressed = false;
        return true;
    }

    if (btn->isHovered) {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        SDL_SetTextureColorMod(btn->texture, btn->hoveredColor.r, btn->hoveredColor.g, btn->hoveredColor.b);
    } else {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
        SDL_SetTextureColorMod(btn->texture, 255, 255, 255);
    }

    SDL_RenderCopy(renderer, btn->texture, NULL, &btn->rect);

    return false;
}

void SpawnEnemy(Enemy* enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) {
            // Si l'ennemi n'est pas actif
            enemies[i].rect.x = rand() % SCREEN_WIDTH;
            enemies[i].rect.y = 0;
            enemies[i].rect.w = ENEMY_SIZE;
            enemies[i].rect.h = ENEMY_SIZE;

            int textureWidth, textureHeight;
            SDL_QueryTexture(textureAsteroid, NULL, NULL, &textureWidth, &textureHeight);

            enemies[i].rect.h = ENEMY_SIZE * textureHeight;
            enemies[i].rect.w = ENEMY_SIZE * textureWidth;

            enemies[i].dx = (rand() % 3 - 1) * 5; // -1, 0, or 1
            enemies[i].dy = (rand() % 6 + 5) / 2.0;
            enemies[i].active = true; // Marquer l'ennemi comme actif
            break;
        }
    }
}

void updateEnemies(Enemy* enemies, Player* player) {
    int activeEnemies = 0; // Compteur d'ennemis actifs

    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            // Si l'ennemi est actif
            activeEnemies++; // Incrémenter le compteur d'ennemis actifs

            enemies[i].rect.x += enemies[i].dx;
            enemies[i].rect.y += enemies[i].dy;

            // Supprimer les ennemis qui sont hors de l'écran
            if (enemies[i].rect.y > SCREEN_HEIGHT) {
                enemies[i].active = false; // Marquer l'ennemi comme inactif
                activeEnemies--; // Décrémenter le compteur d'ennemis actifs
            }

            if (!player->immune && SDL_HasIntersection(&enemies[i].rect, &player->rect)) {
                player->health--;
                player->immune = true;
                player->immuneStartTime = SDL_GetTicks();
            }
        }
    }

    if (player->immune && SDL_GetTicks() - player->immuneStartTime >= 3000) {
        player->immune = false;
    }

    // Si le nombre d'ennemis actifs est inférieur à MIN_ENEMIES, faire apparaître de nouveaux ennemis
    if (activeEnemies < MIN_ENEMIES) {
        SpawnEnemy(enemies);
    }
}

void renderEnemies(SDL_Renderer* renderer,const Enemy* enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            // Si l'ennemi est actif
            SDL_RenderCopy(renderer, textureAsteroid, NULL, &enemies[i].rect);
        }
    }
}

void renderPlayer(SDL_Renderer* renderer,const Player* player) {
    if (player->immune && (SDL_GetTicks() - player->immuneStartTime) % 500 < 250) {
        SDL_SetTextureColorMod(texturePlayer, 255, 0, 0);
    }
    else {
        SDL_SetTextureColorMod(texturePlayer, 255, 255, 255);
    }
    SDL_RenderCopy(renderer, texturePlayer, NULL, &player->rect);
}

void renderHealth(SDL_Renderer* renderer,const Player* player) {
    SDL_Rect heartRect = {10, 10, 40, 40};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (int i = 0; i < player->health; i++) {
        SDL_RenderCopy(renderer, textureHeart, NULL, &heartRect);
        heartRect.x += 50;
    }
}

void renderScore(SDL_Renderer* renderer,const Game* game) {
    char scoreText[20];
    sprintf(scoreText, "Score: %d", game->score);

    SDL_Surface* scoreSurface = TTF_RenderText_Solid(fontMed, scoreText, (SDL_Color){255, 255, 255});
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    const SDL_Rect scoreRect = {SCREEN_WIDTH - scoreSurface->w - 10, 10, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);
}

void gameLoop(SDL_Renderer* renderer) {
    SDL_bool quit = false;
    SDL_Event event;

    // Track key states
    bool isQPressed = false;
    bool isDPressed = false;
    bool isZPressed = false;
    bool isSPressed = false;

    Uint32 lastTick = SDL_GetTicks();
    Uint32 lastScoreTick = SDL_GetTicks();
    Uint32 lastSpawnTime = SDL_GetTicks(); // Dernier moment où un ennemi a été généré
    const Uint32 countdownStartTime = SDL_GetTicks(); // Moment où le décompte a commencé
    Enemy* enemies = malloc(MAX_ENEMIES * sizeof(Enemy));

    int textureWidth, textureHeight;
    SDL_QueryTexture(texturePlayer, NULL, NULL, &textureWidth, &textureHeight);
    Player player = {{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PLAYER_SIZE * textureWidth, PLAYER_SIZE * textureHeight}, 5};

    Game game = {false, 0};

    SDL_Surface* surface1 = IMG_Load("Images/StartButton.png");
    Button startBtn = {
        .hoveredColor = {200, 200, 200},
        .rect = {SCREEN_WIDTH / 2 - 299/2, SCREEN_HEIGHT / 4*3 - 144/2, 299, 144},
        .texture = SDL_CreateTextureFromSurface(renderer, surface1),
    };
    SDL_FreeSurface(surface1);

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_q:
                        case SDLK_LEFT:
                            isQPressed = true;
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            isDPressed = true;
                            break;
                        case SDLK_z:
                        case SDLK_UP:
                            isZPressed = true;
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            isSPressed = true;
                            break;
                        default:
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_q:
                        case SDLK_LEFT:
                            isQPressed = false;
                            break;
                        case SDLK_d:
                        case SDLK_RIGHT:
                            isDPressed = false;
                            break;
                        case SDLK_z:
                        case SDLK_UP:
                            isZPressed = false;
                            break;
                        case SDLK_s:
                        case SDLK_DOWN:
                            isSPressed = false;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            btnProcessEvent(&startBtn, event);
        }

        if (!game.started) {
            SDL_RenderClear(renderer);
            SDL_ShowCursor(true);

            SDL_RenderCopy(renderer, textureMainMenuBackground, NULL, NULL);

            if (renderButton(renderer, &startBtn)) {
                game.started = true;
            }
        }
        else {
            // Vérifier si le décompte est terminé
            if (SDL_GetTicks() - countdownStartTime >= COUNTDOWN_DURATION) {
                // Générer un nouvel ennemi toutes les SPAWN_DELAY millisecondes
                if (SDL_GetTicks() - lastSpawnTime >= SPAWN_DELAY) {
                    SpawnEnemy(enemies);
                    lastSpawnTime = SDL_GetTicks();
                }

                // Update rectangle position based on key states and introduce a delay
                if (lastTick + MOVEMENT_DELAY < SDL_GetTicks()) {
                    if (isQPressed && !isDPressed && player.rect.x > 0) {
                        player.rect.x -= 5;
                    }
                    else if (!isQPressed && isDPressed && player.rect.x < SCREEN_WIDTH - player.rect.w) {
                        player.rect.x += 5;
                    }

                    if (isZPressed && !isSPressed && player.rect.y > 0) {
                        player.rect.y -= 5;
                    }
                    else if (!isZPressed && isSPressed && player.rect.y < SCREEN_HEIGHT - player.rect.h) {
                        player.rect.y += 5;
                    }

                    updateEnemies(enemies, &player);

                    lastTick = SDL_GetTicks();
                }

                if (lastScoreTick + SCORE_DELAY < SDL_GetTicks()) {
                    game.score++;
                    lastScoreTick = SDL_GetTicks();
                }
            }

            SDL_RenderClear(renderer);
            SDL_ShowCursor(false);

            SDL_SetTextureColorMod(textureBackground, 150, 150, 150);
            SDL_RenderCopy(renderer, textureBackground, NULL, NULL);

            if (SDL_GetTicks() - countdownStartTime < COUNTDOWN_DURATION) {
                // Afficher le décompte
                const int countdown = 3 - (SDL_GetTicks() - countdownStartTime) / 1000;
                char countdownText[10];
                sprintf(countdownText, "%d", countdown);

                SDL_Surface* countdownSurface =
                        TTF_RenderText_Solid(fontBig, countdownText, (SDL_Color){255, 255, 255});
                SDL_Texture* countdownTexture = SDL_CreateTextureFromSurface(renderer, countdownSurface);
                SDL_Rect countdownRect = {
                    SCREEN_WIDTH / 2 - countdownSurface->w / 2, SCREEN_HEIGHT / 2 - countdownSurface->h / 2,
                    countdownSurface->w, countdownSurface->h
                };
                SDL_RenderCopy(renderer, countdownTexture, NULL, &countdownRect);
                SDL_FreeSurface(countdownSurface);
                SDL_DestroyTexture(countdownTexture);
            }
            else {
                renderEnemies(renderer, enemies);
                renderPlayer(renderer, &player);
                renderHealth(renderer, &player);
                renderScore(renderer, &game);
            }
        }

        SDL_RenderPresent(renderer);
    }

    free(enemies);
}

int main(int argc, char** argv) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (0 != SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    TTF_Init();

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (NULL == window) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
        fprintf(stderr, "Erreur SDL_SetWindowFullscreen : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    // Rendering

    fontSmall = TTF_OpenFont("arial.ttf", 25);
    fontMed = TTF_OpenFont("arial.ttf", 50);
    fontBig = TTF_OpenFont("arial.ttf", 100);

    SDL_Surface* surface = IMG_Load("Images/asteroid.png");
    textureAsteroid = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Surface* surfaceP = IMG_Load("Images/vaisseau.png");
    texturePlayer = SDL_CreateTextureFromSurface(renderer, surfaceP);
    SDL_FreeSurface(surfaceP);

    SDL_Surface* surfaceH = IMG_Load("Images/heart.png");
    textureHeart = SDL_CreateTextureFromSurface(renderer, surfaceH);
    SDL_FreeSurface(surfaceH);

    SDL_Surface* surfaceB = IMG_Load("Images/background.png");
    textureBackground = SDL_CreateTextureFromSurface(renderer, surfaceB);
    SDL_FreeSurface(surfaceB);

    SDL_Surface* surfaceB2 = IMG_Load("Images/MainMenu.png");
    textureMainMenuBackground = SDL_CreateTextureFromSurface(renderer, surfaceB2);
    SDL_FreeSurface(surfaceB2);

    gameLoop(renderer);

    TTF_CloseFont(fontSmall);
    TTF_CloseFont(fontMed);
    TTF_CloseFont(fontBig);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
