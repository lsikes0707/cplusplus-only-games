#include "raylib.h"

/*
  * Program Name: Dapper Dasher (Game)
  * Summary: hopping side scroller, dodge the collisions
  * Author: Lacey (While sharpening my c++ skills with GameDev.tv)
*/
int main()
{
    // window dimensions
    const int width = 512;      // const variable will not change in the program
    const int height = 380;     // I bet these have to do with the paralaxing image sizes
    const char * windowTitle = "Lacey's Dapper Dasher Game";
    // initialize the window
    InitWindow(width, height, windowTitle);

    bool collision_with_enemy{};

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        if ( collision_with_enemy )
        {
            DrawText("Game Over!", width/2, height/2, 20, RED);
        }
        else
        {
            // Game Logic Start

            DrawText("Level: 1", 10, 10, 20, BLUE);

            // Game Logic End
        }

        EndDrawing();
    }
    CloseWindow();
}