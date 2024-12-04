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
    const char * windowTitle = "Lacey's Dapper Dasher Game";
    // initialize the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // gravity, pixels/frame per frame
    const int gravity{1};

    // rectangle dimensions
    const int rect_w{50};
    const int rect_h{80};

    int posY(windowHeight - rect_h);
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
            if ( posY >= (windowHeight - rect_h) )
            {
                // rectangle is on the ground
                velocity = 0;
            }
            else
            {
                // rectangle is in the air, apply gravity
                velocity += gravity;
            }

            // adding jump with SPACE logic
            if ( IsKeyPressed(KEY_SPACE) )
            {
                // add to the velocity
                velocity -= 10;
            }
            /*else
            {
                velocity = 0;
            }*/


            // update position
            posY += velocity;

            DrawRectangle(windowWidth/2, posY, rect_w, rect_h, BLUE);

            DrawText("Level: 1", 10, 10, 20, BLUE);

            // Game Logic End
        }

        EndDrawing();
    }
    CloseWindow();
}