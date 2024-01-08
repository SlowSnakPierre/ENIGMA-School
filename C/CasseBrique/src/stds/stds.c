#include "../../inc/stds/stds.h"

static char numberBuffer[MAX_INT_DIGITS];
static char textBuffer[MAX_LINE_LENGTH];
static bool seed = false;

int randomInt(const int min, const int max) {
    if (!seed) {
        srand(time(NULL));
        seed = true;
    }
    return rand() % (max - min + 1) + min;
}

float randomFloat(const float min, const float max) {
    if (!seed) {
        srand(time(NULL));
        seed = true;
    }

    const float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

void clamp(int* n, const int min, const int max) {
    if (*n < min) {
        *n = min;
    }
    else if (*n > max) {
        *n = max;
    }
}

void calcSlope(const int x1, const int y1, const int x2, const int y2, float* xSlope, float* ySlope) {
    const int steps = MAX(abs( x1 - x2 ), abs( y1 - y2 ));

    if (steps == 0) {
        *xSlope = *ySlope = 0;
        return;
    }

    *xSlope = x1 - x2;
    *xSlope /= steps;

    *ySlope = y1 - y2;
    *ySlope /= steps;
}

float getAngle(const int x1, const int y1, const int x2, const int y2) {
    const float angle = -90.0f + atan2(y1 - y2, x1 - x2) * (180.0f / PI);
    return angle >= 0 ? angle : 360.0f + angle;
}

int getDistance(const int x1, const int y1, const int x2, const int y2) {
    const int x = x2 - x1;
    const int y = y2 - y1;

    return (int)sqrt(x * x + y * y);
}

void print(const char* s, ...) {
    va_list args;
    memset(&textBuffer, '\0', sizeof(textBuffer));

    va_start(args, s);
    vsprintf(textBuffer, s, args);
    va_end(args);

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", textBuffer);
}

bool isMouseOverRect(const float x, const float y, const SDL_Rect rect) {
    return x > rect.x && x < rect.x + rect.w && (y > rect.y && y < rect.y + rect.h);
}

float toRadians(const float degreeAngle) {
    return degreeAngle * (PI / 180.0f);
}

float toDegrees(const float radianAngle) {
    return radianAngle * (180.0f / PI);
}

char* strSubstring(const char* str, const int first, const int last) {
    const int s_len = strlen(str);
    assert(s_len > 0 && first < last && first >= 0 && last <= s_len);

    char* s = malloc(sizeof(char) * (last - first));
    memcpy(s, str + first, last - first);
    return s;
}

int strIndexOf(const char* s, const char* searchStr) {
    const int s_len = strlen(s);
    const int search_str_len = strlen(searchStr);

    assert(s_len > 0 && s_len >= search_str_len);

    const char* ptr = strstr(s, searchStr);

    if (ptr) {
        const int index = ptr - s;
        return index;
    }

    return -1;
}

char* strcatInt(const char* s, const int n) {
    memset(textBuffer, '\0', sizeof(textBuffer));
    strncat(textBuffer, s, strlen(s));
    const int digits = sprintf(numberBuffer, "%d", n);
    strncat(textBuffer, numberBuffer, digits);
    return textBuffer;
}
