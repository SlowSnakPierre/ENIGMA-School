#include "../inc/brick.h"

static void updateBrickStatus(Entity_T*);

static char* getStringEnum(enum Brick);

Entity_T* addBrick(const float x, const float y, const int flags, const int identifier) {
    Entity_T* b = malloc(sizeof(Entity_T));
    memset(b, 0, sizeof(Entity_T));

    b->x = x;
    b->y = y;
    b->life = 3;
    b->identifier = identifier;

    b->idFlags |= ID_DEFAULT_BRICK_MASK;
    b->flags |= flags;

    const char* strIdentifier = getStringEnum(identifier);
    char buffer[MAX_BUFFER_SIZE] = {0};

    memset(buffer, 0, MAX_BUFFER_SIZE);
    strcat(buffer, "res/img/brick/");
    strcat(buffer, strIdentifier);
    strcat(buffer, "/");
    strcat(buffer, strIdentifier);
    strcat(buffer, "_animated.png");

    b->animation = addSpritesheet(buffer, 7, randomFloat(0.05f, 0.111f), 0, 0);
    memset(buffer, 0, MAX_BUFFER_SIZE);

    memset(buffer, 0, MAX_BUFFER_SIZE);
    strcat(buffer, "res/img/brick/");
    strcat(buffer, strIdentifier);
    strcat(buffer, "/");
    strcat(buffer, strIdentifier);
    strcat(buffer, "_0.png");
    b->texture[0] = loadTexture(buffer);

    memset(buffer, 0, MAX_BUFFER_SIZE);
    for (int i = 1; i <= MAX_DEBRIS_IMGS; i++) {
        const int MAX_DIGIT = 3;
        char intBuffer[MAX_DIGIT];
        sprintf(intBuffer, "%d", i);
        strcat(buffer, "res/img/brick/");
        strcat(buffer, strIdentifier);
        strcat(buffer, "/");
        strcat(buffer, strIdentifier);
        strcat(buffer, "_");
        strcat(buffer, intBuffer);
        strcat(buffer, "_damaged.png");
        b->texture[i] = loadTexture(buffer);

        memset(buffer, 0, MAX_BUFFER_SIZE);
    }

    SDL_QueryTexture(b->texture[0], NULL, NULL, &b->w, &b->h);

    return b;
}

void updateBrick(Entity_T* b) {
    const int randInt = randomInt(1, 2000);
    if (!b->animation->cycleOnce && randInt == 1 && b->life == 3) {
        b->animation->cycleOnce = true;
        b->animation->flags |= ANIMATION_ACTIVE_MASK;
    }

    if (b->animation->cycleOnce) {
        b->animation->posX = b->x;
        b->animation->posY = b->y;
        animationUpdate(b->animation);
    }

    updateBrickStatus(b);
}

void drawBrick(const Entity_T* b) {
    if (b->animation->cycleOnce && b->life == 3) {
        animationDraw(b->animation);
    }
    else {
        blitTexture(b->texture[0], b->x, b->y, false, false);
    }
}

void removeBrick(Entity_T* b) {
    free(b);
}

static void updateBrickStatus(Entity_T* b) {
    switch (b->life) {
        case 3:
            return;
        case 2:
            b->texture[0] = b->texture[1];
            break;
        case 1:
            b->texture[0] = b->texture[2];
            break;
        case 0:
            b->flags |= DEATH_MASK;
            break;
        default:
            break;
    }
}

static char* getStringEnum(enum Brick const b) {
    switch (b) {
        case RED:
            return "red";
        case BLUE:
            return "blue";
        case YELLOW:
            return "yellow";
        case PURPLE:
            return "purple";
        case ORANGE:
            return "orange";
        case LIGHT_BLUE:
            return "light_blue";
        case LIGHT_GREEN:
            return "light_green";
        case DARK_GREEN:
            return "dark_green";
        case BROWN:
            return "brown";
        case NULL_COLOR:
            return "NULL";
        default:
            return "NULL";
    }
}
