#include "Input.h"
#include "DxLib.h"

void UpdateInput(InputState& input)
{
    const bool leftDown = CheckHitKey(KEY_INPUT_LEFT) != 0;
    const bool rightDown = CheckHitKey(KEY_INPUT_RIGHT) != 0;
    const bool spaceDown = CheckHitKey(KEY_INPUT_SPACE) != 0;
    const bool retryDown = CheckHitKey(KEY_INPUT_R) != 0;
    const bool enterDown = CheckHitKey(KEY_INPUT_RETURN) != 0;
    const bool upDown = CheckHitKey(KEY_INPUT_UP) != 0;
    const bool downDown = CheckHitKey(KEY_INPUT_DOWN) != 0;
    const bool menuDown = CheckHitKey(KEY_INPUT_M) != 0;

    input.exitRequested = CheckHitKey(KEY_INPUT_ESCAPE) != 0;
    input.moveDirection = 0;

    if (leftDown)
    {
        --input.moveDirection;
    }
    if (rightDown)
    {
        ++input.moveDirection;
    }

    input.reversePressed = spaceDown && !input.previousSpaceDown;
    input.retryPressed = retryDown && !input.previousRetryDown;
    input.enterPressed = enterDown && !input.previousEnterDown;
    input.upPressed = upDown && !input.previousUpDown;
    input.downPressed = downDown && !input.previousDownDown;
    input.leftPressed = leftDown && !input.previousLeftDown;
    input.rightPressed = rightDown && !input.previousRightDown;
    input.menuPressed = menuDown && !input.previousMenuDown;

    input.previousSpaceDown = spaceDown;
    input.previousRetryDown = retryDown;
    input.previousEnterDown = enterDown;
    input.previousUpDown = upDown;
    input.previousDownDown = downDown;
    input.previousLeftDown = leftDown;
    input.previousRightDown = rightDown;
    input.previousMenuDown = menuDown;
}