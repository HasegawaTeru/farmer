#pragma once

#include "Scene_Game.h"

struct Player
{
    float x;
    float y;
    float velocityX;
    float velocityY;
};

void InitializePlayer(Player& player, float startX, float startY);
void UpdatePlayer(Player& player, int moveDirection, float deltaTime, const Stage& stage);
void DrawPlayer(const Player& player);