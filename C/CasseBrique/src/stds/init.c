#include "../../inc/stds/init.h"

static bool debugMode = true;

static void initSDL(const char*, int, int, int, int);

static void initAudioContext(void);

static void cleanup(void);

void initGame(const char* title, const int w, const int h, const int lw, const int lh) {
    initSDL(title, w, h, lw, lh);
    initSounds();
    initFonts();

    app.originalTitle = title;

    atexit(cleanup);
}

static void initSDL(const char* windowName, const int windowWidth, const int windowHeight, const int levelWidth,
                    const int levelHeight) {
    const int renderer_flags = SDL_RENDERER_ACCELERATED;
    const int window_flags = 0;

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization of SDL started.");
    }

    memset(&app, 0, sizeof(App_T));
    app.SCREEN_WIDTH = windowWidth;
    app.SCREEN_HEIGHT = windowHeight;
    app.LEVEL_WIDTH = levelWidth;
    app.LEVEL_HEIGHT = levelHeight;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s.\n", SDL_GetError());
        exit(11);
    }

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing window.");
    }

    app.window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  windowWidth, windowHeight, window_flags);
    if (!app.window) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not open window. %s.\n", SDL_GetError());
        exit(12);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating SDL renderer.");
    }

    app.renderer = SDL_CreateRenderer(app.window, -1, renderer_flags);
    if (!app.renderer) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize renderer: %s.\n",
                    SDL_GetError());
        exit(13);
    }

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initialization Completed.");
    }

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    SDL_ShowCursor(true);

    initAudioContext();
}

static void initAudioContext(void) {
    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing audio context and SDL Mixer.");
    }

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL Mixer.\n");
        exit(14);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);
}

static void cleanup(void) {
    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Cleaning up.");
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing parallax backgrounds.");
    }

    while (app.parallaxHead.next) {
        ParallaxBackground_T *pbg = app.parallaxHead.next;
        app.parallaxHead.next = pbg->next;
        free(pbg);
    }

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing textures.");
    }

    while (app.textureHead.next) {
        Texture_T* t = app.textureHead.next;
        app.textureHead.next = t->next;
        free(t);
    }

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing trails.");
    }

    while (app.trailHead.next) {
        Trail_T* tr = app.trailHead.next;
        app.trailHead.next = tr->next;
        free(tr);
    }

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Freeing buttons.");
    }

    while (app.buttonHead.next) {
        Button_T* b = app.buttonHead.next;
        app.buttonHead.next = b->next;
        free(b);
    }

    TTF_Quit();
    SDL_Quit();

    if (debugMode) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Program quit.");
    }
}
