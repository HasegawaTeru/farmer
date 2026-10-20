#pragma once

struct InputState
{
    // このフレームにゲームへ渡す入力です。
    int moveDirection;
    bool exitRequested;
    bool reversePressed;
    bool retryPressed;
    bool enterPressed;
    bool upPressed;
    bool downPressed;
    bool leftPressed;
    bool rightPressed;
    bool menuPressed;

    // 押した瞬間を調べるために、前の状態を覚えます。
    bool previousSpaceDown;
    bool previousRetryDown;
    bool previousEnterDown;
    bool previousUpDown;
    bool previousDownDown;
    bool previousLeftDown;
    bool previousRightDown;
    bool previousMenuDown;
};

void UpdateInput(InputState& input);