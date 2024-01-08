#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define SIZE_PERCENT 0.4f

void gameLoop(SDL_Renderer *renderer) {
    SDL_bool quit = false;
    SDL_Event event;

    SDL_Surface *imageSurface = SDL_LoadBMP("image.bmp"); // Load the image file
    SDL_Texture *imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface); // Create a texture from the image surface
    SDL_Rect imageRect = { 0, 0, imageSurface->w * SIZE_PERCENT, imageSurface->h * SIZE_PERCENT }; // Set the image's position and size

    SDL_Surface *imageSurface2 = SDL_LoadBMP("image.bmp"); // Load the image file
    SDL_Texture *imageTexture2 = SDL_CreateTextureFromSurface(renderer, imageSurface2); // Create a texture from the image surface
    SDL_Rect imageRect2 = { SCREEN_WIDTH - (imageSurface2->w * SIZE_PERCENT), 0, imageSurface2->w * SIZE_PERCENT, imageSurface2->h * SIZE_PERCENT }; // Set the image's position and size

    int speedX = 1;
    int speedY = 1;

    int speedX2 = -1;
    int speedY2 = 1;

    while (!quit) {
        srand(time(NULL));

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    // Keybinds
                    switch (event.key.keysym.sym) {
                        // Quit the game on escape
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        // Update the rectangle's position based on its speed
        imageRect.x += speedX;
        imageRect.y += speedY;
        imageRect2.x += speedX2;
        imageRect2.y += speedY2;

        // Check for collisions with the edges of the screen
        if (imageRect.x < 0 || imageRect.x + imageRect.w > SCREEN_WIDTH) {
            int hue1 = rand() % 255;
            int hue2 = rand() % 255;
            int hue3 = rand() % 255;

            SDL_SetTextureColorMod(imageTexture, hue1, hue2, hue3);
            speedX *= -1; // Reverse the horizontal direction
        }

        if (imageRect.y < 0 || imageRect.y + imageRect.h > SCREEN_HEIGHT) {
            int hue1 = rand() % 255;
            int hue2 = rand() % 255;
            int hue3 = rand() % 255;

            SDL_SetTextureColorMod(imageTexture, hue1, hue2, hue3);

            speedY *= -1; // Reverse the vertical direction
        }

        // Check for collisions with the edges of the screen
        if (imageRect2.x < 0 || imageRect2.x + imageRect2.w > SCREEN_WIDTH) {
            int hue1 = rand() % 255;
            int hue2 = rand() % 255;
            int hue3 = rand() % 255;

            SDL_SetTextureColorMod(imageTexture2, hue1, hue2, hue3);
            speedX2 *= -1; // Reverse the horizontal direction
        }

        if (imageRect2.y < 0 || imageRect2.y + imageRect2.h > SCREEN_HEIGHT) {
            int hue1 = rand() % 255;
            int hue2 = rand() % 255;
            int hue3 = rand() % 255;

            SDL_SetTextureColorMod(imageTexture2, hue1, hue2, hue3);

            speedY2 *= -1; // Reverse the vertical direction
        }

        // Collision between the two rectangles
        float centerX1 = imageRect.x + imageRect.w / 2.0f;
        float centerY1 = imageRect.y + imageRect.h / 2.0f;

        float centerX2 = imageRect2.x + imageRect2.w / 2.0f;
        float centerY2 = imageRect2.y + imageRect2.h / 2.0f;

        float distance = sqrtf((centerX1 - centerX2) * (centerX1 - centerX2) + (centerY1 - centerY2) * (centerY1 - centerY2));

        if (distance < imageSurface->w * SIZE_PERCENT) {
            // Generate new random directions for both rectangles
            int newSpeedX = rand() % 2 == 0 ? 1 : -1;
            int newSpeedY = rand() % 2 == 0 ? 1 : -1;

            int newSpeedX2 = newSpeedX * -1;
            int newSpeedY2 = newSpeedY * -1;

            // Adjust the speed of the colliding rectangles to avoid further collision
            speedX = newSpeedX;
            speedY = newSpeedY;

            speedX2 = newSpeedX2;
            speedY2 = newSpeedY2;

            // Change the color of both rectangles to indicate collision
            int hue1 = rand() % 255;
            int hue2 = rand() % 255;
            int hue3 = rand() % 255;
            int hue4 = rand() % 255;
            int hue5 = rand() % 255;
            int hue6 = rand() % 255;

            SDL_SetTextureColorMod(imageTexture, hue1, hue2, hue3);
            SDL_SetTextureColorMod(imageTexture2, hue4, hue5, hue6);
        }

        if (distance < 200.0f) {
            SDL_Delay(20);
        } else {
            SDL_Delay(2);
        }

        SDL_RenderClear(renderer);

        // Render the image onto the screen
        SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);
        SDL_RenderCopy(renderer, imageTexture2, NULL, &imageRect2);

        SDL_RenderPresent(renderer);
    }

    // Free the image resources
    SDL_FreeSurface(imageSurface);
    SDL_DestroyTexture(imageTexture);
    SDL_FreeSurface(imageSurface2);
    SDL_DestroyTexture(imageTexture2);
}

int main(int argc, char **argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (NULL == renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_ShowCursor(false);
    gameLoop(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}