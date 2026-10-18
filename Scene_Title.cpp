#include "Scene_Title.h"
#include "Scene_Game.h"
#include "GameConfig.h"
#include "DxLib.h"

void DrawTitleScreen()
{
    const unsigned int white = GetColor(240, 240, 240);
    const unsigned int cyan = GetColor(80, 210, 255);
    const unsigned int orange = GetColor(255, 180, 80);

    // 床と天井をイメージした飾りです。当たり判定はありません。
    DrawBox(160, 112, WINDOW_W - 161, 127, cyan, TRUE);
    DrawBox(160, 608, WINDOW_W - 161, 623, orange, TRUE);

    SetFontSize(48);
    DrawString(460, 184, "REVERSE GRAVITY", cyan);

    SetFontSize(24);
    DrawString(548, 280, "Enter: Start", white);

    SetFontSize(20);
    DrawString(416, 368, "Left / Right : Move", white);
    DrawString(416, 404, "Space        : Reverse gravity", white);
    DrawString(416, 440, "R            : Retry stage", white);
    DrawString(416, 476, "Esc          : Exit", white);
    DrawString(416, 536, "3 stages / No jump / Unlimited reversals", orange);

    // 次の画面の文字サイズに影響を残さないように戻します。
    SetFontSize(16);
}

void DrawStageSelectScreen(int difficultyIndex, int selectedStageIndex)
{
    const unsigned int white = GetColor(240, 240, 240);
    const unsigned int cyan = GetColor(80, 210, 255);
    const char* difficultyNames[DIFFICULTY_COUNT] = { "EASY", "NORMAL", "HARD" };

    SetFontSize(40);
    DrawString(80, 104, "STAGE SELECT", cyan);

    SetFontSize(24);
    for (int i = 0; i < DIFFICULTY_COUNT; ++i)
    {
        const int y = 260 + i * 56;
        const bool selected = i == difficultyIndex;

        if (selected)
        {
            DrawBox(80, y - 6, 400, y + 34, GetColor(40, 60, 80), TRUE);
        }

        DrawString(100, y, selected ? ">" : " ", cyan);
        DrawString(140, y, difficultyNames[i], selected ? cyan : white);
    }

    DrawFormatString(100, 448, cyan, "< Stage %d >", selectedStageIndex + 1);
    DrawString(560, 216, "PREVIEW", cyan);

    // プレイ中のデータとは別に、表示用のステージを用意します。
    Stage previewStage{};
    InitializeStage(previewStage, difficultyIndex, selectedStageIndex);
    DrawStagePreview(previewStage, 560, 256, 0.5f);

    SetFontSize(16);
    DrawString(80, 528, "Up/Down: Difficulty", white);
    DrawString(80, 560, "Left/Right: Stage", white);
    DrawString(80, 592, "Enter: Start", white);
    DrawString(80, 624, "Esc: Exit", white);
    DrawString(560, 632, previewStage.name, white);
    DrawString(560, 672, "Gray: Ground  Red: Spikes  Green: Exit  Cyan: Start", white);
}