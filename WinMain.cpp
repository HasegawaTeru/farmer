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
    bool previousSpaceDown = false;
    bool previousRetryDown = false;

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

        const bool spaceDown = CheckHitKey(KEY_INPUT_SPACE) != 0;
        const bool retryDown = CheckHitKey(KEY_INPUT_R) != 0;
        const bool reversePressed = spaceDown && !previousSpaceDown;
        const bool retryPressed = retryDown && !previousRetryDown;

        previousSpaceDown = spaceDown;
        previousRetryDown = retryDown;

        // 3. R を押した瞬間はリトライを優先します。
        if (retryPressed)
        {
            InitializePlayer(player, stage.startX, stage.startY);
            accumulatedTime = 0.0f;
        }
        else
        {
            if (reversePressed)
            {
                ReversePlayerGravity(player);
            }

            accumulatedTime += deltaTime;

            while (accumulatedTime >= PHYSICS_STEP)
            {
                UpdatePlayer(player, moveDirection, PHYSICS_STEP, stage);
                accumulatedTime -= PHYSICS_STEP;

                // ミスをすぐ検出できるよう、物理更新のたびに調べます。
                if (IsPlayerDead(player, stage))
                {
                    InitializePlayer(player, stage.startX, stage.startY);
                    accumulatedTime = 0.0f;
                    break;
                }
            }
        }

        // 4. 現在の状態を描画します。
        ClearDrawScreen();
        DrawStage(stage);
        DrawPlayer(player);

        DrawString(24, 24,
            "Step 6 - Left/Right: Move / Space: Reverse / R: Retry / Esc: Exit",
            textColor);

        DrawString(24, 44,
            player.gravityDirection == 1 ? "Gravity: DOWN" : "Gravity: UP",
            textColor);

        DrawString(620, 44, "Red zones: spikes", textColor);

        ScreenFlip();
        WaitTimer(1);
    }

    DxLib_End();
    return 0;
}