#include "Scene_Game.h"
#include "DxLib.h"

void InitializeStage(Stage& stage, int stageIndex)
{
    // 衝突・ミス確認用のステージです。床には落下用の穴があります。
    stage = {
        {
            {   0,  64, 1280,  32 }, // 天井
            {   0, 656, 1040,  64 }, // 床の左側
            {1160, 656,  120,  64 }, // 床の右側
            {   0,  96,   32, 560 }, // 左の壁
            {1248,  96,   32, 560 }, // 右の壁
            { 360, 480,  240,  24 }, // 足場
            { 880, 496,   32, 160 }  // 床から伸びる壁
        },
        7,
        420.0f, 300.0f,
        {
            { {640, 632, 120, 24}, -1 },
            { {760,  96, 120, 24},  1 }
        },
        2,
        {} // 出口はステージ番号に応じて下で設定します。
    };

    // 今回は切り替え確認用に、同じ地形で出口の位置を変えます。
    if (stageIndex == 0)
    {
        stage.goal = { 540, 416, 48, 64 }; // 足場の右側
    }
    else if (stageIndex == 1)
    {
        stage.goal = { 96, 592, 48, 64 }; // 床の左側
    }
    else
    {
        stage.goal = { 96, 96, 48, 64 }; // 天井の左側
    }
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

    const int goalX = static_cast<int>(stage.goal.x);
    const int goalY = static_cast<int>(stage.goal.y);
    const unsigned int goalColor = GetColor(70, 200, 120);

    DrawBox(goalX, goalY,
        goalX + static_cast<int>(stage.goal.width) - 1,
        goalY + static_cast<int>(stage.goal.height) - 1,
        goalColor, TRUE);

    DrawString(goalX + 8, goalY + 24, "EXIT", GetColor(10, 35, 20));

    const unsigned int dangerColor = GetColor(100, 30, 40);
    const unsigned int spikeColor = GetColor(245, 70, 80);

    for (int i = 0; i < stage.spikeCount; ++i)
    {
        const Spike& spike = stage.spikes[i];
        const int x = static_cast<int>(spike.bounds.x);
        const int y = static_cast<int>(spike.bounds.y);
        const int width = static_cast<int>(spike.bounds.width);
        const int height = static_cast<int>(spike.bounds.height);

        // 背景も塗り、矩形全体に当たり判定があることを示します。
        DrawBox(x, y, x + width - 1, y + height - 1, dangerColor, TRUE);

        int toothCount = width / 24;
        if (toothCount < 1)
        {
            toothCount = 1;
        }

        const int baseY = (spike.direction == -1) ? y + height - 1 : y;
        const int tipY = (spike.direction == -1) ? y : y + height - 1;

        for (int tooth = 0; tooth < toothCount; ++tooth)
        {
            const int left = x + tooth * width / toothCount;
            const int right = x + (tooth + 1) * width / toothCount - 1;

            DrawTriangle(left, baseY, right, baseY,
                (left + right) / 2, tipY, spikeColor, TRUE);
        }
    }
}