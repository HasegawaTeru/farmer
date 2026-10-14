#pragma once

// プレイヤー1人分の状態です。座標は四角形の左上を表します。
struct Player
{
    float x;
    float y;
    float velocityX;
};

// 宣言：ほかの cpp ファイルから呼べる処理を示します。
void InitializePlayer(Player& player, float startX, float startY);
void UpdatePlayer(Player& player, int moveDirection, float deltaTime);
void DrawPlayer(const Player& player);