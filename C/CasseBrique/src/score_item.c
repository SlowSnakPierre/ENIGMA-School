#include "../inc/score_item.h"

#define BRICK_SCORE 100

void addScoreItem(const float x, const float y, const int score) {
    const int MAX_DIGITS = 5;

    ScoreItem_T* s = malloc(sizeof(ScoreItem_T));
    memset(s, 0, sizeof(ScoreItem_T));

    s->x = x;
    s->y = y;
    s->life = 100;

    s->score = score == 0 ? BRICK_SCORE : score;

    if (currentLevel->lastBreakTimer && score == 0) {
        s->score *= currentLevel->lastBreakTimer;
    }

    stage.score += s->score;
    char numberBuffer[MAX_DIGITS] = {};
    sprintf(numberBuffer, "%d", s->score);
    strcat(s->text, numberBuffer);
    currentLevel->scoreItemTail->next = s;
    currentLevel->scoreItemTail = s;
}

void updateScoreItem(ScoreItem_T* s) {
    if (--s->life <= 0) {
        s->flags |= DEATH_MASK;
        currentLevel->lastBreakTimer = 0;
    }
}

void drawScoreItem(const ScoreItem_T* s) {
    drawText(s->x, s->y, 255, 255, 255, "res/fonts/arcadia.ttf", 20, s->text);
}
