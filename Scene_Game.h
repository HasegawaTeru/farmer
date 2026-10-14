#pragma once

#include "GameConfig.h"

// x, y ‚Í¶ã‚ÌÀ•WBwidth, height ‚Í•‚Æ‚‚³‚Å‚·B
struct Rect
{
    float x;
    float y;
    float width;
    float height;
};

struct Stage
{
    Rect solids[MAX_SOLIDS];
    int solidCount;
    float startX;
    float startY;
};

void InitializeStage(Stage& stage);
void DrawStage(const Stage& stage);