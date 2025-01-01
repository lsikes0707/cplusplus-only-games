#include "Character.h"

Character::Character()
{
    width = texture.width / maxFrames;
    height = texture.height;
}

void Character::setScreenPosition(int winWidth, int winHeight) // fully qualifying the function
{
    // define the function outside the Character class
    screenPosition = {
        (float)winWidth/2.0f - 4.0f * (0.5f * width),    // c-style cast
        (float)winHeight/2.0f - 4.0f * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { direction.x -= 1.0; }   // move direction left
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { direction.x += 1.0; }   // move direction right
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) { direction.y -= 1.0; }   // move direction up
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { direction.y += 1.0; }   // move direction down
    if (Vector2Length(direction) != 0.0)
    {
        // set worldPosition = worldPosition + direction
        worldPosition = Vector2Add(worldPosition, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // ternary operator
        texture = run;// update player idleness
    }
    else
    {
        texture = idle;
    }

    // update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
    }

    // draw the player
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPosition.x, screenPosition.y, 2.0f * width, 2.0f * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}