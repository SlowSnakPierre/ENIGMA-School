#include "../../inc/stds/button.h"

void drawButtons(void) {
    for (Button_T* b = app.buttonHead.next; b != NULL; b = b->next) {
        buttonDraw(b);
    }
}

Button_T* addButton(const float x, const float y, const int w, const int h, const bool filled,
                    const char* fontDirectory, const int fontSize, const SDL_Color* fontColor, const char* text) {
    Button_T* button = malloc(sizeof(Button_T));

    if (button == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Error: could not allocate memory for Button_T, %s.\n",
                    SDL_GetError());
        exit(5);
    }

    memset(button, 0, sizeof(Button_T));
    const SDL_Color black = {0, 0, 0};
    button->rect.x = (int)x;
    button->rect.y = (int)y;
    button->rect.w = w;
    button->rect.h = h;
    button->fontPath = fontDirectory;
    button->fontSize = fontSize;
    button->color = black;
    button->textColor = *fontColor;
    button->isFilled = filled;

    int fw, fh;
    getStringSize(text, button->fontPath, button->fontSize, &fw, &fh);

    button->textX = button->rect.x + (button->rect.w - fw) / 2;
    button->textY = button->rect.y + (button->rect.h - fh) / 2;

    return button;
}

Button_T* addButtonTexture(const float x, const float y, const char* textureDirectory, const char* fontDirectory,
                           const int fontSize, const SDL_Color* color,
                           const char* text) {
    Button_T* button = malloc(sizeof(Button_T));

    if (button == NULL) {
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                    "Error: could not allocate memory for Button_T, %s.\n", SDL_GetError());
        exit(6);
    }

    memset(button, 0, sizeof(Button_T));

    button->textureId = 0;
    button->texture[button->textureId] = loadTexture(textureDirectory);

    button->rect.x = (int)x;
    button->rect.y = (int)y;
    button->fontPath = fontDirectory;
    button->fontSize = fontSize;
    button->scaleX = 1.0f;
    button->scaleY = 1.0f;
    button->text = text;
    button->textColor = *color;

    SDL_QueryTexture(button->texture[button->textureId], NULL, NULL, &button->rect.w, &button->rect.h);

    int fw, fh;
    getStringSize(text, button->fontPath, button->fontSize, &fw, &fh);

    button->textX = button->rect.x + (button->rect.w - fw) / 2;
    button->textY = button->rect.y + (button->rect.h - fh) / 2;

    return button;
}

void buttonDraw(Button_T* button) {
    if (button->texture[button->textureId] != NULL) {
        blitTextureScaled(button->texture[button->textureId], button->rect.x, button->rect.y, button->scaleX,
                          button->scaleY, 0, SDL_FLIP_NONE, true);
    }
    else {
        drawRect(&button->rect, &button->color, button->isFilled, true);
    }
    drawText(button->textX, button->textY, button->textColor.r, button->textColor.g, button->textColor.b,
             button->fontPath, button->fontSize, button->text);
}

bool isMouseOverButton(const Button_T* button) {
    const int mx = app.mouse.x;
    const int my = app.mouse.y;

    const int x = button->rect.x;
    const int y = button->rect.y;
    const int w = button->rect.w;
    const int h = button->rect.h;
    return mx > x && mx < x + w && (my > y && my < y + h);
}

bool isButtonClicked(const Button_T* button, const int mouseCode) {
    assert(mouseCode == SDL_BUTTON_LEFT || mouseCode == SDL_BUTTON_RIGHT);

    if (isMouseOverButton(button) && app.mouse.button[mouseCode]) {
        app.mouse.button[mouseCode] = 0;
        return true;
    }

    return false;
}
