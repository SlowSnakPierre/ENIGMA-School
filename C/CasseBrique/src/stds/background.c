#include "../../inc/stds/background.h"

static char input_buffer[MAX_BUFFER_SIZE];

void initParallaxBackground(const char* bgDirectory, const size_t n, const float defaultScrollSpeeds,
                            const float modifiedScrollSpeed[], const bool isInfinite) {
    for (int i = 0; i < n; i++) {
        const uint8_t NUM_DIGITS = 3;
        const char* file_extsn = ".png";
        char number_buffer[NUM_DIGITS];
        ParallaxBackground_T* layer = malloc(sizeof(ParallaxBackground_T));

        if (layer == NULL) {
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                        "Could not allocate memory for parallax_background_t. %s.\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        memset(layer, 0, sizeof(ParallaxBackground_T));

        sprintf(number_buffer, "%d", i);
        strcpy(input_buffer, bgDirectory);
        strcat(input_buffer, number_buffer);
        const char* file_name_ext = strcat(input_buffer, file_extsn);
        layer->background = initBackground(file_name_ext);
        layer->parallaxScrollSpeed = modifiedScrollSpeed[i];
        layer->normalScrollSpeed = defaultScrollSpeeds;
        layer->infiniteScroll = isInfinite;

        memset(input_buffer, '\0', sizeof(input_buffer));
        app.parallaxTail->next = layer;
        app.parallaxTail = layer;
    }
}

void parallaxBackgroundUpdate(const ParallaxBackground_T* parallax) {
    if (!parallax->infiniteScroll) {
        parallax->background->x =
                ((0 - app.camera.x) * (parallax->normalScrollSpeed * parallax->parallaxScrollSpeed));

        parallax->background->x = (float)fmod(parallax->background->x, parallax->background->w);
    }
    else {
        parallax->background->x -= (parallax->normalScrollSpeed * parallax->parallaxScrollSpeed);
        if (parallax->background->x < -parallax->background->w) {
            parallax->background->x = 0;
        }
    }
}

void parallaxBackgroundDraw(const ParallaxBackground_T* parallax) {
    blitTextureScaled(parallax->background->backgroundTexture, parallax->background->x, parallax->background->y,
                      parallax->background->scaleX, parallax->background->scaleY, 0, SDL_FLIP_NONE, false);
    blitTextureScaled(parallax->background->backgroundTexture, parallax->background->x + parallax->background->w,
                      parallax->background->y, parallax->background->scaleX, parallax->background->scaleY, 0,
                      SDL_FLIP_NONE, false);
}

Background_T* initBackground(const char* bgDirectory) {
    Background_T* background = malloc(sizeof(Background_T));

    if (background == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not allocate memory for background_t. %s.\n",
                    SDL_GetError());
        exit(EXIT_FAILURE);
    }

    memset(background, 0, sizeof(Background_T));

    background->x = 0;
    background->y = 0;

    int32_t w;
    int32_t h;

    background->backgroundTexture = loadTexture(bgDirectory);
    SDL_QueryTexture(background->backgroundTexture, NULL, NULL, &w, &h);

    background->w = w;
    background->h = h;
    background->scaleX = 1.0;
    background->scaleY = 1.0;

    return background;
}

void backgroundDraw(const Background_T* bg) {
    blitTextureScaled(bg->backgroundTexture, bg->x, bg->y,
                      bg->scaleX, bg->scaleY, 0, SDL_FLIP_NONE, false);
}

void backgroundDie(Background_T* bg) {
    SDL_DestroyTexture(bg->backgroundTexture);
    free(bg);
}
