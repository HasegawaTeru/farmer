#include "Game.h"
#include "GameConfig.h"

static void RestartPlayer(GameData& game)
{
    InitializePlayer(game.player, game.stage.startX, game.stage.startY);
    game.accumulatedTime = 0.0f;
}

static void StartStage(GameData& game, int stageIndex)
{
    game.stageIndex = stageIndex;
    InitializeStage(game.stage, game.difficultyIndex, game.stageIndex);
    RestartPlayer(game);
    game.state = GameState::Playing;
}

static void UpdateStageSelection(GameData& game, const InputState& input)
{
    if (input.upPressed && !input.downPressed && game.difficultyIndex > 0)
    {
        --game.difficultyIndex;
    }
    if (input.downPressed && !input.upPressed &&
        game.difficultyIndex < DIFFICULTY_COUNT - 1)
    {
        ++game.difficultyIndex;
    }
    if (input.leftPressed && !input.rightPressed && game.selectedStageIndex > 0)
    {
        --game.selectedStageIndex;
    }
    if (input.rightPressed && !input.leftPressed &&
        game.selectedStageIndex < STAGES_PER_DIFFICULTY - 1)
    {
        ++game.selectedStageIndex;
    }
    if (input.enterPressed)
    {
        StartStage(game, game.selectedStageIndex);
    }
}

static void UpdatePlaying(GameData& game, const InputState& input, float deltaTime)
{
    if (input.retryPressed)
    {
        RestartPlayer(game);
        return;
    }

    if (input.reversePressed)
    {
        ReversePlayerGravity(game.player);
    }

    game.accumulatedTime += deltaTime;
    while (game.accumulatedTime >= PHYSICS_STEP)
    {
        UpdatePlayer(game.player, input.moveDirection, PHYSICS_STEP, game.stage);
        game.accumulatedTime -= PHYSICS_STEP;

        // ミスとクリアが重なった場合は、ミスを優先します。
        if (IsPlayerDead(game.player, game.stage))
        {
            RestartPlayer(game);
            break;
        }
        if (IsPlayerAtGoal(game.player, game.stage))
        {
            game.state = (game.stageIndex + 1 < STAGE_COUNT)
                ? GameState::StageClear : GameState::AllClear;
            game.accumulatedTime = 0.0f;
            break;
        }
    }
}

void InitializeGame(GameData& game)
{
    game = {};
    game.state = GameState::Title;
    InitializeStage(game.stage, game.difficultyIndex, game.stageIndex);
    RestartPlayer(game);
}

void UpdateGame(GameData& game, const InputState& input, float deltaTime)
{
    const bool canReturnToStageSelect =
        game.state == GameState::Playing ||
        game.state == GameState::StageClear ||
        game.state == GameState::AllClear;

    if (input.menuPressed && canReturnToStageSelect)
    {
        game.selectedStageIndex = game.stageIndex;
        game.accumulatedTime = 0.0f;
        game.state = GameState::StageSelect;
        return;
    }

    switch (game.state)
    {
    case GameState::Title:
        game.accumulatedTime = 0.0f;
        if (input.enterPressed)
        {
            game.state = GameState::StageSelect;
        }
        break;

    case GameState::StageSelect:
        game.accumulatedTime = 0.0f;
        UpdateStageSelection(game, input);
        break;

    case GameState::StageClear:
        game.accumulatedTime = 0.0f;
        if (input.enterPressed)
        {
            StartStage(game, game.stageIndex + 1);
        }
        break;

    case GameState::AllClear:
        game.accumulatedTime = 0.0f;
        if (input.enterPressed)
        {
            game.state = GameState::Title;
        }
        break;

    case GameState::Playing:
        UpdatePlaying(game, input, deltaTime);
        break;
    }
}