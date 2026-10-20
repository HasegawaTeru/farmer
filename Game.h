#pragma once

#include "Input.h"
#include "Player.h"
#include "Scene_Game.h"

enum class GameState
{
    Title,
    StageSelect,
    Playing,
    StageClear,
    AllClear
};

struct GameData
{
    GameState state;          // 現在の画面
    int stageIndex;           // プレイ中の面番号
    int difficultyIndex;      // 選択した難易度
    int selectedStageIndex;   // 選択画面の面番号
    Stage stage;
    Player player;
    float accumulatedTime;   // 未処理の物理更新時間
};

int RunGame();
void InitializeGame(GameData& game);
void UpdateGame(GameData& game, const InputState& input, float deltaTime);
void DrawGame(const GameData& game);