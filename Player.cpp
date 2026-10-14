#include "Player.h"
#include "GameConfig.h"
#include "DxLib.h"

void InitializePlayer(Player& player, float startX, float startY)
{
    player.x = startX;
    player.y = startY;
    player.velocityX = 0.0f;
}

void UpdatePlayer(Player& player, int moveDirection, float deltaTime)
{
    // moveDirection は左なら -1、停止なら 0、右なら 1 です。
    player.velocityX = moveDirection * PLAYER_MOVE_SPEED;
    player.x += player.velocityX * deltaTime;

    // プレイヤー全体が画面内に収まるように補正します。
    if (player.x < 0.0f)
    {
        player.x = 0.0f;
    }
    if (player.x > WINDOW_W - PLAYER_SIZE)
    {
        player.x = static_cast<float>(WINDOW_W - PLAYER_SIZE);
    }
}

void DrawPlayer(const Player& player)
{
    // 描画するときだけ整数に変換します。
    const int drawX = static_cast<int>(player.x);
    const int drawY = static_cast<int>(player.y);
    const unsigned int color = GetColor(80, 210, 255);

    DrawBox(drawX, drawY,
        drawX + PLAYER_SIZE - 1, drawY + PLAYER_SIZE - 1,
        color, TRUE);
}