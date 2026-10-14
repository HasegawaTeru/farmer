#include "Player.h"
#include "GameConfig.h"
#include "DxLib.h"

void InitializePlayer(Player& player, float startX, float startY)
{
    player.x = startX;
    player.y = startY;
    player.velocityX = 0.0f;
    player.velocityY = 0.0f;
    player.gravityDirection = 1;
}

void ReversePlayerGravity(Player& player)
{
    player.gravityDirection *= -1;
    player.velocityY = 0.0f;
}

void UpdatePlayer(Player& player, int moveDirection, float deltaTime,
    const Stage& stage)
{
    // 1. 横に移動し、横方向の衝突だけを解決します。
    player.velocityX = moveDirection * PLAYER_MOVE_SPEED;
    const float oldX = player.x;
    const float moveX = player.velocityX * deltaTime;
    player.x += moveX;

    for (int i = 0; i < stage.solidCount; ++i)
    {
        const Rect& solid = stage.solids[i];

        // 上下に重なっていない地形は、横移動を妨げません。
        if (player.y + PLAYER_SIZE <= solid.y ||
            player.y >= solid.y + solid.height)
        {
            continue;
        }

        if (moveX > 0.0f && oldX + PLAYER_SIZE <= solid.x &&
            player.x + PLAYER_SIZE >= solid.x)
        {
            player.x = solid.x - PLAYER_SIZE;
            player.velocityX = 0.0f;
        }
        else if (moveX < 0.0f && oldX >= solid.x + solid.width &&
            player.x <= solid.x + solid.width)
        {
            player.x = solid.x + solid.width;
            player.velocityX = 0.0f;
        }
    }

    // 2. 重力で縦速度を変え、速さを制限します。
    player.velocityY += GRAVITY * player.gravityDirection * deltaTime;

    if (player.velocityY > MAX_FALL_SPEED)
    {
        player.velocityY = MAX_FALL_SPEED;
    }
    if (player.velocityY < -MAX_FALL_SPEED)
    {
        player.velocityY = -MAX_FALL_SPEED;
    }

    // 3. 縦に移動し、縦方向の衝突だけを解決します。
    const float oldY = player.y;
    const float moveY = player.velocityY * deltaTime;
    player.y += moveY;

    for (int i = 0; i < stage.solidCount; ++i)
    {
        const Rect& solid = stage.solids[i];

        if (player.x + PLAYER_SIZE <= solid.x ||
            player.x >= solid.x + solid.width)
        {
            continue;
        }

        if (moveY > 0.0f && oldY + PLAYER_SIZE <= solid.y &&
            player.y + PLAYER_SIZE >= solid.y)
        {
            player.y = solid.y - PLAYER_SIZE;
            player.velocityY = 0.0f;
        }
        else if (moveY < 0.0f && oldY >= solid.y + solid.height &&
            player.y <= solid.y + solid.height)
        {
            player.y = solid.y + solid.height;
            player.velocityY = 0.0f;
        }
    }
}

bool IsPlayerDead(const Player& player, const Stage& stage)
{
    // プレイヤー全体が画面の外へ出たらミスにします。
    if (player.x + PLAYER_SIZE <= 0.0f || player.x >= WINDOW_W ||
        player.y + PLAYER_SIZE <= 0.0f || player.y >= WINDOW_H)
    {
        return true;
    }

    for (int i = 0; i < stage.spikeCount; ++i)
    {
        const Rect& spike = stage.spikes[i].bounds;

        // 端が接触した場合もミスにします。
        if (player.x <= spike.x + spike.width &&
            player.x + PLAYER_SIZE >= spike.x &&
            player.y <= spike.y + spike.height &&
            player.y + PLAYER_SIZE >= spike.y)
        {
            return true;
        }
    }

    return false;
}

void DrawPlayer(const Player& player)
{
    const int drawX = static_cast<int>(player.x);
    const int drawY = static_cast<int>(player.y);

    const unsigned int color = (player.gravityDirection == 1)
        ? GetColor(80, 210, 255)
        : GetColor(255, 180, 80);

    DrawBox(drawX, drawY,
        drawX + PLAYER_SIZE - 1, drawY + PLAYER_SIZE - 1,
        color, TRUE);
}