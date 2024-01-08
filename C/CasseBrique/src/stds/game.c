#include "../../inc/stds/game.h"

static int currentFps;

static void capFramerate(long*, float*);

static int updateWindowTitle(int, void*);

void initAppStructures(void) {
    app.textureTail = &app.textureHead;
    app.buttonTail = &app.buttonHead;
    app.trailTail = &app.trailHead;
    app.fontTail = &app.fontHead;
}

void initWindowFps(void) {
#ifndef __APPLE__
    SDL_AddTimer(WINDOW_UPDATE_TIMER, updateWindowTitle, &currentFps);
#endif
}

void loop(void) {
    long then;
    float remainder;

    then = SDL_GetTicks();

    while (true) {
        prepareScene();
        processInput();
        app.delegate.tick();
        app.delegate.draw();
        presentScene();
        capFramerate(&then, &remainder);
    }
}

static void capFramerate(long* then, float* remainder) {
    long wait = (int)(FPS_TIME + *remainder);
    *remainder -= (int)*remainder;
    const long frameTime = SDL_GetTicks() - *then;
    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);

    currentFps = 1000 / wait;
    *remainder += 0.667f;
    *then = SDL_GetTicks();
}

static int updateWindowTitle(const int interval, void* args) {
    const int fps = *(int *)args;
    char* windowBuffer = malloc(sizeof(char) * SMALL_TEXT_BUFFER);

    if (windowBuffer == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Error: could not allocate memory for the window buffer: %s.\n", SDL_GetError());
        exit(10);
    }

    strcpy(windowBuffer, app.originalTitle);

    strcat(windowBuffer, " | FPS: ");

    windowBuffer = strcatInt(windowBuffer, fps);
    SDL_SetWindowTitle(app.window, windowBuffer);
    return interval;
}
