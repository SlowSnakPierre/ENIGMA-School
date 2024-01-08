#ifndef STRUCTS_H
#define STRUCTS_H

#include "stds.h"

typedef struct Delegate Delegate_T;
typedef struct Entity Entity_T;
typedef struct Mouse Mouse_T;
typedef struct App App_T;
typedef struct Animation Animation_T;
typedef struct Texture Texture_T;
typedef struct FadeColor FadeColor_T;
typedef struct Background Background_T;
typedef struct ParallaxBackground ParallaxBackground_T;
typedef struct Font Font_T;
typedef struct Trail Trail_T;
typedef struct Button Button_T;
typedef struct ParticleSystem ParticleSystem_T;
typedef struct Particle Particle_T;

struct Button {
    const char* text;
    const char* fontPath;
    bool isFilled;

    int textureId;
    int textX;
    int textY;
    int fontSize;
    float scaleX;
    float scaleY;

    SDL_Texture* texture[TEXTURE_BUFFER_SIZE];
    SDL_Color color;
    SDL_Color textColor;
    SDL_Rect rect;

    Button_T* next;
};

struct Particle {
    float x;
    float y;
    float dx;
    float dy;
    float deltaAccelX;
    float deltaAccelY;
    float deltaAlpha;
    int w;
    int h;
    int angle;
    int life;
    int idFlags;
    int flags;

    SDL_Color color;
    SDL_Texture* currentTexture;

    Animation_T* animation;

    void (*particleUpdate)(Particle_T*);

    void (*particleDraw)(Particle_T*);
};

struct ParticleSystem {
    int aliveCount;
    int deadIndex;
    int maxParticles;

    Particle_T* particles;
};

struct ParallaxBackground {
    float parallaxScrollSpeed;
    float normalScrollSpeed;
    bool infiniteScroll;

    Background_T* background;
    ParallaxBackground_T* next;
};

struct Trail {
    float x;
    float y;
    int alpha;
    int alphaDecayRate;
    int flags;
    bool isTexture;

    SDL_RendererFlip flip;
    SDL_Texture* texture;

    Trail_T* next;
};

struct Animation {
    float posX;
    float posY;

    int spliceX;
    int spliceY;
    int w;
    int h;
    int angle;
    int startX;
    int startY;
    int spriteSheetWidth;
    int spriteSheetHeight;
    bool cycleOnce;

    int idFlags;
    int flags;
    int currentFrameId;
    size_t numberOfFrames;
    float frameDelay;
    float frameTimer;

    SDL_RendererFlip flip;

    SDL_Texture* currentTexture;
    SDL_Texture* defaultTexture;
    SDL_Texture** frames;
    SDL_Texture* spriteSheet;

    Animation_T* next;
};

struct Background {
    float x;
    float y;
    float scrollX;
    float scrollY;

    int w;
    int h;

    float scaleX;
    float scaleY;

    SDL_Texture* backgroundTexture;
};

struct Texture {
    char name[MAX_FILE_NAME_LEN];

    SDL_Texture* texture;

    Texture_T* next;
};

struct Font {
    char name[MAX_FILE_NAME_LEN];
    int size;

    TTF_Font* font;
    Font_T* next;
};

struct Delegate {
    void (*tick)(void);

    void (*draw)(void);
};

struct Mouse {
    int x;
    int y;
    int button[MAX_MOUSE_BUTTONS];
    int wheel;
};

struct App {
    int keyboard[MAX_KEYBOARD_KEYS];

    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int LEVEL_WIDTH;
    int LEVEL_HEIGHT;
    const char* originalTitle;

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Rect screen_bounds;
    SDL_Rect camera;

    Mouse_T mouse;
    Delegate_T delegate;
    Trail_T trailHead, *trailTail;
    Texture_T textureHead, *textureTail;
    Font_T fontHead, *fontTail;
    ParallaxBackground_T parallaxHead, *parallaxTail;
    Button_T buttonHead, *buttonTail;

    enum GameState gameState;
};

struct FadeColor {
    bool isFirstColor;
    float alpha;
    float time;

    SDL_Color c1;
    SDL_Color c2;
};

struct Entity {
    float x;
    float y;

    float variability;

    float scaleX;
    float scaleY;

    float dx;
    float dy;

    float deltaAccelX;
    float deltaAccelY;

    float deltaAlpha;

    int w;
    int h;
    int flags;
    int idFlags;
    int reload;
    int identifier;

    int angle;
    int radius;

    int health;
    int life;

    SDL_Color color;
    SDL_Texture* texture[TEXTURE_BUFFER_SIZE];

    Animation_T* animation;
    Entity_T* next;

    void (*tick)(Entity_T*);

    void (*draw)(Entity_T*);

    void (*touch)(Entity_T*);

    void (*die)(Entity_T*);
};

#endif
