#include "Scene_Game.h"
#include "DxLib.h"

void InitializeStage(Stage& stage)
{
    // 今回は衝突確認用のステージです。完成版の3面は後で作ります。
    stage = {
        {
            {   0,  64, 1280,  32 }, // 天井
            {   0, 656, 1280,  64 }, // 床
            {   0,  96,   32, 560 }, // 左の壁
            {1248,  96,   32, 560 }, // 右の壁
            { 360, 480,  240,  24 }, // 足場
            { 880, 496,   32, 160 }  // 床から伸びる壁
        },
        6,            // 実際に使う地形の数
        420.0f, 300.0f // 開始位置
    };
}

void DrawStage(const Stage& stage)
{
    const unsigned int color = GetColor(100, 115, 140);
    for (int i = 0; i < stage.solidCount; ++i)
    {
        const Rect& solid = stage.solids[i];
        const int x = static_cast<int>(solid.x);
        const int y = static_cast<int>(solid.y);
        DrawBox(x, y,
            x + static_cast<int>(solid.width) - 1,
            y + static_cast<int>(solid.height) - 1,
            color, TRUE);
    }
}