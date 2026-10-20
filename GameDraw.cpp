#include "Game.h"
#include "GameConfig.h"
#include "Scene_Title.h"
#include "DxLib.h"

void DrawGame(const GameData& game)
{
    const unsigned int textColor = GetColor(240, 240, 240);
    const char* difficultyNames[DIFFICULTY_COUNT] = {
        "EASY", "NORMAL", "HARD"
    };

    ClearDrawScreen();

    switch (game.state)
    {
    case GameState::Title:
        DrawTitleScreen();
        break;

    case GameState::StageSelect:
        DrawStageSelectScreen(game.difficultyIndex, game.selectedStageIndex);
        break;

    case GameState::Playing:
        DrawStage(game.stage);
        DrawPlayer(game.player);

        DrawString(24, 24,
            "Left/Right: Move / Space: Reverse / R: Retry / M: Select / Esc: Exit",
            textColor);
        DrawString(24, 44,
            game.player.gravityDirection == 1 ? "Gravity: DOWN" : "Gravity: UP",
            textColor);
        DrawFormatString(300, 44, textColor,
            "Difficulty: %s", difficultyNames[game.difficultyIndex]);
        DrawFormatString(650, 44, textColor,
            "Stage: %d / %d", game.stageIndex + 1, STAGES_PER_DIFFICULTY);
        DrawString(960, 44, "Red zones: spikes", textColor);
        break;

    case GameState::StageClear:
        DrawStageClearScreen(
            difficultyNames[game.difficultyIndex], game.stageIndex + 1);
        break;

    case GameState::AllClear:
        DrawAllClearScreen(difficultyNames[game.difficultyIndex]);
        break;
    }
}