#include "Scene_Title.h"
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
    DrawString(416, 536,
        "3 stages / No jump / Unlimited reversals", orange);

    // 次の画面の文字サイズに影響を残さないように戻します。
    SetFontSize(16);
}

void DrawStageSelectScreen()
{
    const unsigned int white = GetColor(240, 240, 240);
    const unsigned int cyan = GetColor(80, 210, 255);

    SetFontSize(40);
    DrawString(480, 180, "STAGE SELECT", cyan);

    SetFontSize(24);
    DrawString(440, 300, "Enter: Play Stage 1", white);
    DrawString(440, 348, "Esc: Exit", white);

    // ゲーム画面へ文字サイズの変更を持ち越さないようにします。
    SetFontSize(16);
}