#ifndef SCORE_ITEM_H
#define SCORE_ITEM_H

#include "stds/draw.h"
#include "stds/text.h"
#include "commons.h"
#include "score_item.h"

extern Level_T *currentLevel;
extern Stage_T stage;

extern void addScoreItem(float, float, int);
extern void updateScoreItem(ScoreItem_T *);
extern void drawScoreItem(const ScoreItem_T *);
#endif