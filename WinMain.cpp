#include "WinMain.h"
#include "GameConfig.h"
#include "Player.h"
#include "Scene_Game.h"
#include "Scene_Title.h"

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

    int stageIndex = 0; // 内部の番号は 0、1、2 です。
    GameState gameState = GameState::Title;

    Stage stage{};
    InitializeStage(stage, stageIndex);

    Player player{};
    InitializePlayer(player, stage.startX, stage.startY);

    const unsigned int textColor = GetColor(240, 240, 240);
    LONGLONG previousTime = GetNowHiPerformanceCount();
    float accumulatedTime = 0.0f;
    bool previousSpaceDown = false;
    bool previousRetryDown = false;
    bool previousEnterDown = false;

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
        const bool enterDown = CheckHitKey(KEY_INPUT_RETURN) != 0;

        const bool reversePressed = spaceDown && !previousSpaceDown;
        const bool retryPressed = retryDown && !previousRetryDown;
        const bool enterPressed = enterDown && !previousEnterDown;

        previousSpaceDown = spaceDown;
        previousRetryDown = retryDown;
        previousEnterDown = enterDown;

        // 3. クリア後は物理更新を止め、Enter を待ちます。
        if (gameState == GameState::Title)
        {
            accumulatedTime = 0.0f;

            if (enterPressed)
            {
                gameState = GameState::StageSelect;
            }
        }
        else if (gameState == GameState::StageSelect)
        {
            accumulatedTime = 0.0f;

            if (enterPressed)
            {
                stageIndex = 0;
                InitializeStage(stage, stageIndex);
                InitializePlayer(player, stage.startX, stage.startY);
                gameState = GameState::Playing;
            }
        }
        else if (gameState == GameState::StageClear)
        {
            accumulatedTime = 0.0f;

            if (enterPressed)
            {
                ++stageIndex;
                InitializeStage(stage, stageIndex);
                InitializePlayer(player, stage.startX, stage.startY);
                gameState = GameState::Playing;
            }
        }
        else if (gameState == GameState::AllClear)
        {
            accumulatedTime = 0.0f;

            if (enterPressed)
            {
                gameState = GameState::Title;
            }
        }
        else if (retryPressed)
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

                // ミスを先に調べます。
                if (IsPlayerDead(player, stage))
                {
                    InitializePlayer(player, stage.startX, stage.startY);
                    accumulatedTime = 0.0f;
                    break;
                }

                // ミスと出口に同時に触れた場合は、ミスを優先します。
                if (IsPlayerAtGoal(player, stage))
                {
                    gameState = (stageIndex + 1 < STAGE_COUNT)
                        ? GameState::StageClear : GameState::AllClear;

                    accumulatedTime = 0.0f;
                    break;
                }
            }
        }

        // 4. 現在の状態を描画します。
        ClearDrawScreen();

        if (gameState == GameState::Title)
        {
            DrawTitleScreen();
        }
        else if (gameState == GameState::StageSelect)
        {
            DrawStageSelectScreen();
        }
        else if (gameState == GameState::Playing)
        {
            DrawStage(stage);
            DrawPlayer(player);

            DrawString(24, 24,
                "Left/Right: Move / Space: Reverse / R: Retry / Esc: Exit",
                textColor);

            DrawString(24, 44,
                player.gravityDirection == 1 ? "Gravity: DOWN" : "Gravity: UP",
                textColor);

            DrawString(620, 44, "Red zones: spikes", textColor);

            DrawFormatString(1000, 44, textColor,
                "Stage: %d / %d", stageIndex + 1, STAGE_COUNT);
        }
        else if (gameState == GameState::StageClear)
        {
            DrawStageClearScreen(stageIndex + 1);
        }
        else if (gameState == GameState::AllClear)
        {
            DrawAllClearScreen();
        }   

        ScreenFlip();
        WaitTimer(1);
    }

    DxLib_End();
    return 0;
}