#include "WinMain.h"
#include "GameConfig.h"
#include "Player.h"
#include "Scene_Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ChangeWindowMode(TRUE);
    SetGraphMode(WINDOW_W, WINDOW_H, 32);
    SetMainWindowText("Reverse Gravity");
    SetBackgroundColor(24, 28, 40);
    SetWaitVSyncFlag(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    Stage stage{};
    InitializeStage(stage);

    Player player{};
    InitializePlayer(player, stage.startX, stage.startY);

    const unsigned int textColor = GetColor(240, 240, 240);
    LONGLONG previousTime = GetNowHiPerformanceCount();
    float accumulatedTime = 0.0f;

    while (ProcessMessage() == 0)
    {
        // 1. 経過時間を求めます。
        const LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = static_cast<float>(currentTime - previousTime)
            / 1000000.0f;
        previousTime = currentTime;

        if (deltaTime > MAX_DELTA_TIME)
        {
            deltaTime = MAX_DELTA_TIME;
        }

        // 2. 入力を取得します。
        if (CheckHitKey(KEY_INPUT_ESCAPE) != 0)
        {
            break;
        }

        int moveDirection = 0;
        if (CheckHitKey(KEY_INPUT_LEFT) != 0)
        {
            --moveDirection;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT) != 0)
        {
            ++moveDirection;
        }

        // 3. 経過時間をため、物理を常に同じ時間幅で更新します。
        accumulatedTime += deltaTime;

        while (accumulatedTime >= PHYSICS_STEP)
        {
            UpdatePlayer(player, moveDirection, PHYSICS_STEP, stage);
            accumulatedTime -= PHYSICS_STEP;
        }

        // 4. 現在の状態を描画します。
        ClearDrawScreen();
        DrawStage(stage);
        DrawPlayer(player);
        DrawString(24, 24,
            "Step 4 - Gravity & Collision / Left/Right: Move / Esc: Exit",
            textColor);
        ScreenFlip();
        WaitTimer(1);
    }

    DxLib_End();
    return 0;
}