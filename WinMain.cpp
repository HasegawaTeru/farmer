#include "WinMain.h"
#include "GameConfig.h"
#include "Player.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
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

    Player player{};
    InitializePlayer(player, 96.0f, 600.0f);
    const unsigned int textColor = GetColor(240, 240, 240);
    LONGLONG previousTime = GetNowHiPerformanceCount();

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

        // 3. プレイヤーの状態を更新します。
        UpdatePlayer(player, moveDirection, deltaTime);

        // 4. 現在の状態を描画します。
        ClearDrawScreen();
        DrawPlayer(player);
        DrawString(24, 24, "Step 3 - Left/Right: Move / Esc: Exit", textColor);
        ScreenFlip();
        WaitTimer(1);
    }

    DxLib_End();
    return 0;
}