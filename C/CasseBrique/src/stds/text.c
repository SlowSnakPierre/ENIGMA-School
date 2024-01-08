#include "../../inc/stds/draw.h"

#define DEFAULT_FONT_COLOR 255

static char textBuffer[MAX_LINE_LENGTH];
static SDL_Surface* messageSurface;
static SDL_Texture* messageTexture;
static SDL_Rect messageRect;

static TTF_Font* getFont(const char*, int);

static void loadFonts();

static void addFont(const char*, int);

void initFonts(void) {
    app.fontTail = &app.fontHead;
    if (TTF_Init() == -1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize TTF_Init: %s.\n",
                    SDL_GetError());
        exit(16);
    }

    loadFonts();
}

void drawText(const float x, const float y, const int r, const int g, const int b, const char* fontString,
              const int fontSize, const char* text, ...) {
    messageRect.x = (int)x;
    messageRect.y = (int)y;

    va_list args;
    memset(&textBuffer, '\0', sizeof(textBuffer));

    va_start(args, text);
    vsprintf(textBuffer, text, args);
    va_end(args);

    const SDL_Color textColor = {r, g, b};
    TTF_Font* font = getFont(fontString, fontSize);
    messageSurface = TTF_RenderText_Solid(font, textBuffer, textColor);
    TTF_SizeText(font, textBuffer, &messageRect.w, &messageRect.h);

    if (messageSurface == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to write message: %s.\n", SDL_GetError());
        exit(17);
    }

    messageTexture = SDL_CreateTextureFromSurface(app.renderer, messageSurface);
    SDL_RenderCopy(app.renderer, messageTexture, NULL, &messageRect);
    SDL_DestroyTexture(messageTexture);
    SDL_FreeSurface(messageSurface);
}

void getStringSize(const char* s, const char* font, const int size, int* w, int* h) {
    TTF_Font* f = getFont(font, size);

    if (f != NULL) {
        TTF_SizeText(f, s, w, h);
    }
    else {
        exit(18);
    }
}

static TTF_Font* getFont(const char* font_str, const int fontSize) {
    for (const Font_T* f = app.fontHead.next; f != NULL; f = f->next) {
        if (strcmp(f->name, font_str) == 0 && f->size == fontSize) {
            return f->font;
        }
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not find font %s, %d.", font_str, fontSize);

    return NULL;
}

static void loadFonts(void) {
    addFont("res/fonts/arcadia.ttf", 16);
    addFont("res/fonts/arcadia.ttf", 20);
    addFont("res/fonts/arcadia.ttf", 26);
    addFont("res/fonts/arcadia.ttf", 48);
}

static void addFont(const char* fontFile, const int size) {
    Font_T* f = malloc(sizeof(Font_T));

    if (f == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for font_t. %s.\n",
                    SDL_GetError());
        exit(19);
    }

    memset(f, 0, sizeof(Font_T));

    f->font = TTF_OpenFont(fontFile, size);

    if (f->font == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not load font_t %s, %d. Is the path correct?",
                    fontFile, size);
    }

    strcpy(f->name, fontFile);
    f->size = size;

    app.fontTail->next = f;
    app.fontTail = f;
}
