#include "Game.h"
#include "GameConfig.h"
#include "DxLib.h"

int RunGame()
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

    GameData game{};
    InitializeGame(game);
    InputState input{};
    LONGLONG previousTime = GetNowHiPerformanceCount();

    while (ProcessMessage() == 0)
    {
        const LONGLONG currentTime = GetNowHiPerformanceCount();
        float deltaTime = static_cast<float>(currentTime - previousTime)
            / 1000000.0f;
        previousTime = currentTime;

        if (deltaTime > MAX_DELTA_TIME)
        {
            deltaTime = MAX_DELTA_TIME;
        }

        UpdateInput(input);
        if (input.exitRequested)
        {
            break;
        }

        UpdateGame(game, input, deltaTime);
        DrawGame(game);
        ScreenFlip();
        WaitTimer(1);
    }

    DxLib_End();
    return 0;
}