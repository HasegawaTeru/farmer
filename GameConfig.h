#pragma once

constexpr int WINDOW_W = 1280;
constexpr int WINDOW_H = 720;
constexpr int PLAYER_SIZE = 40;
constexpr int MAX_SOLIDS = 32; // ステージに置ける地形の最大数
constexpr int MAX_SPIKES = 32; // トゲの領域の最大数

constexpr float PLAYER_MOVE_SPEED = 300.0f; // ピクセル/秒
constexpr float GRAVITY = 1800.0f;          // ピクセル/秒/秒
constexpr float MAX_FALL_SPEED = 900.0f;    // ピクセル/秒
constexpr float MAX_DELTA_TIME = 0.1f;      // 秒
constexpr float PHYSICS_STEP = 1.0f / 120.0f; // 物理を更新する時間幅（秒）