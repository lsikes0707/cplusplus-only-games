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

    // gravity, pixels/s per s
    const int gravity{1'000};

    // texture 2D - scarfy player character
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyRect;       // access variables with .
    scarfyRect.width = scarfy.width/6;
    scarfyRect.height = scarfy.height;
    scarfyRect.x = 0;
    scarfyRect.y = 0;
    Vector2 scarfyPos;          // access variables with .
    scarfyPos.x = windowWidth/2 - scarfyRect.width/2;
    scarfyPos.y = windowHeight - scarfyRect.height;

    // texture 2D - nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRect;
    nebRect.x = 0;
    nebRect.y = 0;
    nebRect.width = nebula.width/8;
    nebRect.height = nebula.height/8;
    Vector2 nebPos{windowWidth, windowHeight-nebRect.height};
    
    // nebula x velocity (pixels/second)
    int nebVelocity{0-600};
    
    // animation frame
    int frame{};        // initializing to 0
    // time based animation
    const float updateTime = 1.0/12.0;  // amount of time before we update animation frame
    float runningTime{};


    // is the character in the air
    bool isInAir{};
    // jump velocity (pixels/second(s))
    const int jumpVelocity{-600};

    int velocity{0};

    bool collision_with_enemy{};

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {

        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
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
                velocity += gravity * dT;
                isInAir = true;
            }

            // adding jump with SPACE logic and jump check
            if ( IsKeyPressed(KEY_SPACE) && !isInAir )
            {
                // add jumpVelocity to the velocity
                velocity += jumpVelocity;
            }

            //update nebula position
            nebPos.x += nebVelocity * dT;

            // update position
            scarfyPos.y += velocity * dT;

            if ( !isInAir )
            {
                // update running time
                runningTime += dT;
                // check if running time has surpassed update time
                if (runningTime >= updateTime)
                {
                    runningTime = 0.0;
                    // update animation frame
                    scarfyRect.x = frame * scarfyRect.width;
                    frame++;
                    if (frame > 5)
                    {
                        frame = 0;
                    }
                }
            }

            // draw nebular hazard
            DrawTextureRec(nebula, nebRect, nebPos, WHITE);

            // draw scarfy
            DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

            // Basic UI/HUD
            DrawText("Level: 1", 10, 10, 20, BLUE);

            // Game Logic End
        }

        // end drawing
        EndDrawing();
    }
    // clean up after run and exit
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}