#include "Scene_Game.h"
#include "DxLib.h"

static void InitializeEasyStage(Stage& stage, int stageIndex)
{
    // 前のステージのデータを消します。
    stage = {};

    // 全面に共通する天井、床、左右の壁です。
    stage.solids[0] = { 0, 64, 1280, 32 };
    stage.solids[1] = { 0, 656, 1280, 64 };
    stage.solids[2] = { 0, 96, 32, 560 };
    stage.solids[3] = { 1248, 96, 32, 560 };
    stage.solidCount = 4;
    stage.startX = 96.0f;
    stage.startY = 616.0f;

    if (stageIndex == 0)
    {
        // EASY 1：危険のない場所で、床から天井へ移動します。
        stage.name = "EASY 1 - First reversal";
        stage.hint = "Press Space to reach the ceiling, then move right.";
        stage.goal = { 1168, 96, 48, 64 };
    }
    else if (stageIndex == 1)
    {
        // EASY 2：床のトゲを天井で避け、天井のトゲを床で避けます。
        stage.name = "EASY 2 - Floor and ceiling";
        stage.hint = "Use the ceiling first. Switch down between the red zones.";

        stage.spikes[0] = { {360, 632, 200, 24}, -1 };
        stage.spikes[1] = { {760, 96, 200, 24}, 1 };
        stage.spikeCount = 2;

        stage.goal = { 1168, 576, 48, 80 };
    }
    else
    {
        // EASY 3：空中で下向きに反転し、高い足場へ着地します。
        stage.name = "EASY 3 - Land from midair";
        stage.hint = "Rise beside the block, reverse in midair, then move onto it.";

        stage.solids[4] = { 480, 400, 240, 256 };
        stage.solidCount = 5;

        // 足場の上の天井を危険にし、空中での反転を促します。
        stage.spikes[0] = { {400, 96, 440, 24}, 1 };
        stage.spikeCount = 1;

        stage.goal = { 1168, 576, 48, 80 };
    }
}

static void InitializeNormalStage(Stage& stage, int stageIndex)
{
    stage = {};

    // NORMALの3面に共通する外周と開始位置です。
    stage.solids[0] = { 0, 64, 1280, 32 };
    stage.solids[1] = { 0, 656, 1280, 64 };
    stage.solids[2] = { 0, 96, 32, 560 };
    stage.solids[3] = { 1248, 96, 32, 560 };
    stage.solidCount = 4;
    stage.startX = 96.0f;
    stage.startY = 616.0f;

    if (stageIndex == 0)
    {
        stage.name = "NORMAL 1 - Three red zones";
        stage.hint = "Ceiling, floor, ceiling. Stop in each gap before reversing.";

        stage.spikes[0] = { {320, 632, 200, 24}, -1 };
        stage.spikes[1] = { {640, 96, 200, 24}, 1 };
        stage.spikes[2] = { {960, 632, 160, 24}, -1 };
        stage.spikeCount = 3;

        stage.goal = { 1168, 96, 48, 64 };
    }
    else if (stageIndex == 1)
    {
        stage.name = "NORMAL 2 - Above and below";
        stage.hint = "Go above the first wall, below the second, then up to EXIT.";

        stage.solids[4] = { 360, 400, 48, 256 };
        stage.solids[5] = { 760, 96, 48, 256 };
        stage.solidCount = 6;

        stage.spikes[0] = { {520, 96, 200, 24}, 1 };
        stage.spikes[1] = { {960, 632, 160, 24}, -1 };
        stage.spikeCount = 2;

        stage.goal = { 1168, 96, 48, 64 };
    }
    else
    {
        stage.name = "NORMAL 3 - Midair rest stops";
        stage.hint = "Land on the middle platform. Rest under the hanging wall.";

        stage.solids[4] = { 400, 480, 40, 176 }; // 床から伸びる壁
        stage.solids[5] = { 460, 464, 260, 24 }; // 中央の足場
        stage.solids[6] = { 840, 96, 80, 224 };  // 下面で休める壁
        stage.solidCount = 7;

        stage.spikes[0] = { {360, 632, 640, 24}, -1 };
        stage.spikes[1] = { {240, 96, 760, 24}, 1 };
        stage.spikeCount = 2;

        stage.goal = { 1168, 576, 48, 80 };
    }
}

void InitializeStage(Stage& stage, int difficultyIndex, int stageIndex)
{
    switch (difficultyIndex)
    {
    case 1:
        InitializeNormalStage(stage, stageIndex);
        break;

    case 2:
        // HARD専用の地形は、今後追加します。
        InitializeEasyStage(stage, stageIndex);
        stage.name = "HARD - Temporary layout";
        break;

    default:
        // 0はEASYです。
        InitializeEasyStage(stage, stageIndex);
        break;
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

    // 床の下側にステージ名とヒントを表示します。
    const unsigned int textColor = GetColor(240, 240, 240);
    DrawString(48, 676, stage.name, textColor);
    DrawString(48, 698, stage.hint, textColor);
}

void DrawStageClearScreen(int stageNumber)
{
    const unsigned int white = GetColor(240, 240, 240);
    const unsigned int green = GetColor(70, 200, 120);

    SetFontSize(40);
    DrawString(420, 220, "STAGE CLEAR!", green);

    SetFontSize(24);
    DrawFormatString(452, 304, white,
        "Stage %d / %d completed", stageNumber, STAGE_COUNT);
    DrawString(452, 364, "Enter: Next stage", white);
    DrawString(452, 412, "Esc: Exit", white);

    SetFontSize(16);
}

void DrawAllClearScreen()
{
    const unsigned int white = GetColor(240, 240, 240);
    const unsigned int green = GetColor(70, 200, 120);

    SetFontSize(40);
    DrawString(384, 220, "ALL STAGES CLEAR!", green);

    SetFontSize(24);
    DrawString(432, 320, "You mastered gravity!", white);
    DrawString(432, 376, "Enter: Back to title", white);
    DrawString(432, 424, "Esc: Exit", white);

    SetFontSize(16);
}

namespace
{
    // ステージ内の座標を、プレビュー内の座標に変換します。
    void DrawPreviewRect(const Rect& rect, int drawX, int drawY,
        float scale, unsigned int color)
    {
        const int left = drawX + static_cast<int>(rect.x * scale);
        const int top = drawY + static_cast<int>(rect.y * scale);
        const int right = drawX
            + static_cast<int>((rect.x + rect.width) * scale) - 1;
        const int bottom = drawY
            + static_cast<int>((rect.y + rect.height) * scale) - 1;

        DrawBox(left, top, right, bottom, color, TRUE);
    }
}

void DrawStagePreview(const Stage& stage, int drawX, int drawY, float scale)
{
    const int width = static_cast<int>(WINDOW_W * scale);
    const int height = static_cast<int>(WINDOW_H * scale);

    DrawBox(drawX, drawY, drawX + width - 1, drawY + height - 1,
        GetColor(18, 22, 32), TRUE);

    for (int i = 0; i < stage.solidCount; ++i)
    {
        DrawPreviewRect(stage.solids[i], drawX, drawY, scale,
            GetColor(100, 115, 140));
    }

    for (int i = 0; i < stage.spikeCount; ++i)
    {
        DrawPreviewRect(stage.spikes[i].bounds, drawX, drawY, scale,
            GetColor(245, 70, 80));
    }

    DrawPreviewRect(stage.goal, drawX, drawY, scale,
        GetColor(70, 200, 120));

    const Rect start = {
        stage.startX, stage.startY,
        static_cast<float>(PLAYER_SIZE), static_cast<float>(PLAYER_SIZE)
    };
    DrawPreviewRect(start, drawX, drawY, scale,
        GetColor(80, 210, 255));

    DrawBox(drawX - 2, drawY - 2, drawX + width + 1, drawY + height + 1,
        GetColor(180, 190, 210), FALSE);
}