#pragma once

#include "Scene_Game.h"

struct Player
{
    float x;
    float y;
    float velocityX;
    float velocityY;
    int gravityDirection; // ‰ºŒü‚«‚Í 1AãŒü‚«‚Í -1
};

void InitializePlayer(Player& player, float startX, float startY);
void ReversePlayerGravity(Player& player);
void UpdatePlayer(Player& player, int moveDirection, float deltaTime,
    const Stage& stage);
bool IsPlayerDead(const Player& player, const Stage& stage);
void DrawPlayer(const Player& player);