#include "../inc/hud.h"

static SDL_Texture* heartTexture;
static FadeColor_T fadeColor;
static char* title = "CASSE-BRIQUE";
static char* pregame_text = "APPUYEZ SUR ESPACE POUR COMMENCER !";

static Button_T* playButton;
static Button_T* exitButton;

static void drawLives(const SDL_Color*);

static void drawPregameText(const SDL_Color*);

static void drawScore(const SDL_Color*);

static void drawLevelNumber(void);

static void spawnStarParticles(float, float);

void initHUD(void) {
    heartTexture = loadTexture("res/img/life.png");
    loadMusic("res/sfx/music/menu.ogg");
    playMusic(true);

    SDL_Color c1;
    SDL_Color c2;

    c1.r = 255;
    c1.g = 0;
    c1.b = 0;
    c1.a = 1;

    c2.r = 0;
    c2.g = 255;
    c2.b = 0;
    c2.a = 1;

    fadeColor.c1 = c1;
    fadeColor.c2 = c2;
    fadeColor.time = 0.0f;
    fadeColor.alpha = 0.01f;
}

void initMenu(void) {
    SDL_Color play_color;
    play_color.r = 255;
    play_color.g = 255;
    play_color.b = 255;

    playButton = addButtonTexture(app.SCREEN_WIDTH / 2 - 150, app.SCREEN_HEIGHT / 2 + 40,
                                   "res/img/ui/buttonStock1.png", "res/fonts/arcadia.ttf", 26,
                                   &play_color, "JOUER");
    playButton->texture[1] = loadTexture("res/img/ui/buttonStock1h.png");

    exitButton = addButtonTexture(app.SCREEN_WIDTH / 2 - 150, app.SCREEN_HEIGHT / 2 + 160,
                                   "res/img/ui/buttonStock1.png", "res/fonts/arcadia.ttf", 26,
                                   &play_color, "QUITTER");
    exitButton->texture[1] = loadTexture("res/img/ui/buttonStock1h.png");

    app.buttonTail->next = playButton;
    app.buttonTail = playButton;

    app.buttonTail->next = exitButton;
    app.buttonTail = exitButton;
}

void updateHUD(void) {
    if (stage.state == MENU) {
        updateMenu();
    }
    else {
        spawnStarParticles(randomFloat(400.0f, 2000.0f), randomFloat(900.0f, 1100.0f));
    }
}

void updateMenu(void) {
    if (isMouseOverButton(playButton)) {
        playButton->textureId = 1;
    }
    else {
        playButton->textureId = 0;
    }

    if (isMouseOverButton(exitButton)) {
        exitButton->textureId = 1;
    }
    else {
        exitButton->textureId = 0;
    }

    if (isButtonClicked(playButton, SDL_BUTTON_LEFT)) {
        stage.state = GAME;
        playMusic(false);
        loadLevelMusic(stage.levelId);
    }
    else if (isButtonClicked(exitButton, SDL_BUTTON_LEFT)) {
        exit(EXIT_SUCCESS);
    }
}

void drawHUD(void) {
    SDL_Color c = combineFadeColor(&fadeColor);
    c.a = 255;

    if (stage.state == MENU) {
        drawButtons();
        drawMenu(&c);
    }

    if (stage.state == GAME) {
        drawLives(&c);
        drawScore(&c);
    }

    if (app.gameState == PREGAME && stage.state == GAME) {
        drawLevelNumber();
        drawPregameText(&c);
    }
}

void drawMenu(const SDL_Color* c) {
    int fw, fh;
    getStringSize(title, "res/fonts/arcadia.ttf", 26, &fw, &fh);
    drawText((app.SCREEN_WIDTH >> 1) - ((fw/4)*7 >> 1), 250, c->r, c->g, c->b, "res/fonts/arcadia.ttf",
             48, title);
}

void pausedHUD(void) {
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = app.SCREEN_WIDTH;
    r.h = app.SCREEN_HEIGHT;

    SDL_Color c;
    c.r = c.g = c.b = 0;
    c.a = 128;

    drawRect(&r, &c, true, false);
    int fw, fh;
    getStringSize("EN PAUSE", "res/fonts/arcadia.ttf", 26, &fw, &fh);
    drawText(app.SCREEN_WIDTH / 2 - fw / 2, app.SCREEN_HEIGHT / 2, 255, 255, 255,
             "res/fonts/arcadia.ttf", 26, "EN PAUSE");
    buttonDraw(exitButton);

    if (isMouseOverButton(exitButton)) {
        exitButton->textureId = 1;
    }
    else {
        exitButton->textureId = 0;
    }

    if (isButtonClicked(exitButton, SDL_BUTTON_LEFT)) {
        exit(EXIT_SUCCESS);
    }
}

static void drawLives(const SDL_Color* c) {
    int fw, fh;
    int tw, th;
    const int initial_offset = 20;
    const int offset = 5;

    drawText(initial_offset, initial_offset, c->r, c->g, c->b, "res/fonts/arcadia.ttf", 16, "VIES: ");

    SDL_QueryTexture(heartTexture, NULL, NULL, &tw, &th);
    getStringSize("VIES: ", "res/fonts/arcadia.ttf", 16, &fw, &fh);

    const int v_offset = initial_offset + fh + offset;

    for (int i = 0, x = initial_offset; i < paddle->life; i++, x += tw + offset) {
        blitTexture(heartTexture, x, v_offset, false, false);
    }
}

static void drawPregameText(const SDL_Color* c) {
    int fw, fh;
    getStringSize(pregame_text, "res/fonts/arcadia.ttf", 20, &fw, &fh);
    drawText(app.SCREEN_WIDTH / 2 - fw / 2,
             (app.SCREEN_HEIGHT >> 1) + app.SCREEN_HEIGHT / 4, c->r, c->g, c->b,
             "res/fonts/arcadia.ttf", 20, pregame_text);
}

static void drawScore(const SDL_Color* c) {
    int fw, fh;
    const int offset = 20;
    getStringSize("Score:", "res/fonts/arcadia.ttf", 16, &fw, &fh);
    const int v_offset = offset + fh + 5;

    drawText(app.SCREEN_WIDTH - fw - offset, offset, c->r, c->g, c->b, "res/fonts/arcadia.ttf", 16, "Score:");

    drawText(app.SCREEN_WIDTH - fw - offset, v_offset, 255, 255, 255, "res/fonts/arcadia.ttf", 16, "%d", stage.score);
}

static void drawLevelNumber() {
    int fw, fh;
    const int MAX_DIGITS = 3;

    char level_data[MAX_BUFFER_SIZE];
    char number_buffer[MAX_DIGITS];

    sprintf(number_buffer, "%d", stage.levelId);
    strcpy(level_data, "NIVEAU ");
    strcat(level_data, number_buffer);
    strcat(level_data, "");

    getStringSize(level_data, "res/fonts/arcadia.ttf", 26, &fw, &fh);
    drawText(app.SCREEN_WIDTH / 2 - fw / 2,
             (app.SCREEN_HEIGHT >> 1) + app.SCREEN_HEIGHT / 5, 255, 255, 255,
             "res/fonts/arcadia.ttf", 26, level_data);
}

static void spawnStarParticles(const float x, const float y) {
    const int n = 20;
    for (int i = 0; i < n; i++) {
        Particle_T p;

        const float dx = -10;
        const float dy = -10;

        const int w = randomInt(1, 3);
        const int h = w;
        const int r = 255;
        const int g = 255;
        const int b = 255;
        const int a = randomInt(5, 15);

        const int flags = ID_P_STAR_MASK;
        p = addParticle(x, y, dx, dy, 0, 0, w, h, 0, r, g, b, a, 0, flags | ID_P_SQUARE_MASK);
        insertParticle(ps, &p);
    }
}
