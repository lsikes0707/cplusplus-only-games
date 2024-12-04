#include "raylib.h"

/*
  * Program Name: Dapper Dasher (Game)
  * Summary: hopping side scroller, dodge the collisions
  * Author: Lacey (While sharpening my c++ skills with GameDev.tv)
*/
int main()
{
    // window dimensions
    const int windowWidth = 512;      // const variable will not change in the program
    const int windowHeight = 380;     // I bet these have to do with the paralaxing image sizes
    const char * windowTitle = "Lacey's Dapper Dasher!";
    // initialize the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // gravity, pixels/frame per frame
    const int gravity{1};

    // texture 2D - scrafy player character
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;       // access variables with .
    scarfyRect.width = scarfy.width/6;
    scarfyRect.height = scarfy.height;
    scarfyRect.x = 0;
    scarfyRect.y = 0;
    Vector2 scarfyPos;          // access variables with .
    scarfyPos.x = windowWidth/2 - scarfyRect.width/2;
    scarfyPos.y = windowHeight - scarfyRect.height;
    


    // is the rectangle in the air
    bool isInAir{};
    // jump velocity
    const int jumpVelocity{-22};

    int velocity{0};

    bool collision_with_enemy{};

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if ( collision_with_enemy )
        {
            DrawText("Game Over!", windowWidth/2, windowHeight/2, 20, RED);
        }
        else
        {
            // Game Logic Start

            // perform ground check
            if ( scarfyPos.y >= (windowHeight - scarfyRect.height) )
            {
                // rectangle is on the ground
                velocity = 0;
                isInAir = false;
            }
            else
            {
                // rectangle is in the air, apply gravity
                velocity += gravity;
                isInAir = true;
            }

            // adding jump with SPACE logic and jump check
            if ( IsKeyPressed(KEY_SPACE) && !isInAir )
            {
                // add jumpVelocity to the velocity
                velocity += jumpVelocity;
            }

            // update position
            scarfyPos.y += velocity;

            // draw scarfy
            DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

            DrawText("Level: 1", 10, 10, 20, BLUE);

            // Game Logic End
        }

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}