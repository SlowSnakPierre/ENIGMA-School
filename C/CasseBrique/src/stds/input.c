#include "../../inc/stds/input.h"

static void keyPressed(const SDL_KeyboardEvent*);

static void keyReleased(const SDL_KeyboardEvent*);

static void mousePressed(const SDL_MouseButtonEvent*);

static void mouseReleased(const SDL_MouseButtonEvent*);

void processInput(void) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        SDL_GetMouseState(&app.mouse.x, &app.mouse.y);
        switch (event.type) {
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
            case SDL_KEYDOWN:
                keyPressed(&event.key);
                break;
            case SDL_KEYUP:
                keyReleased(&event.key);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePressed(&event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                mouseReleased(&event.button);
                break;
            case SDL_MOUSEWHEEL:
                app.mouse.wheel = event.wheel.y;
                break;
            default:
                break;
        }
    }
}

static void keyPressed(const SDL_KeyboardEvent* event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 1;
    }
}

static void keyReleased(const SDL_KeyboardEvent* event) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = 0;
    }
}

static void mousePressed(const SDL_MouseButtonEvent* event) {
    app.mouse.button[event->button] = 1;
}

static void mouseReleased(const SDL_MouseButtonEvent* event) {
    app.mouse.button[event->button] = 0;
}
