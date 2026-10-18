#pragma once

#include "GameConfig.h"

// x, y は左上の座標。width, height は幅と高さです。
struct Rect
{
    float x;
    float y;
    float width;
    float height;
};

// 赤い矩形全体を危険な範囲とします。
struct Spike
{
    Rect bounds;
    int direction; // 見た目の向き。上向きは -1、下向きは 1
};

struct Stage
{
    Rect solids[MAX_SOLIDS];
    int solidCount;
    float startX;
    float startY;
    Spike spikes[MAX_SPIKES];
    int spikeCount;
    Rect goal;
    const char* name;
    const char* hint;
};

void InitializeStage(Stage& stage, int difficultyIndex, int stageIndex);
void DrawStage(const Stage& stage);
void DrawStageClearScreen(int stageNumber);
void DrawAllClearScreen();
void DrawStagePreview(const Stage& stage, int drawX, int drawY, float scale);