#include "raylib.h"

/*
  * Program Name: Dapper Dasher (Game)
  * Summary: hopping side scroller, dodge the collisions
  * Author: Lacey (While sharpening my c++ skills with GameDev.tv)
*/
struct AnimationData
{
    Rectangle rect;
    Vector2 position;
    int frame;
    float updateTime;
    float runningTime;
};

// function to return boolean whether or not something is on the ground
bool isOnGround(AnimationData data, int windowHeight)
{
    return data.position.y >= windowHeight - data.rect.height;
}
// return AnimationData
AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrame)
{
    // update runningTime
    data.runningTime += deltaTime;
    if ( data.runningTime >= data.updateTime )
    {
        // reset runningTime to zero
        data.runningTime = 0.0;
        // update animation frame
        data.rect.x = data.frame * data.rect.width;
        data.frame++;
        if ( data.frame > maxFrame )
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // window dimensions
    double windowDimensions[2];
    windowDimensions[0] = 512;
    windowDimensions[1] = 380;
    const char * windowTitle = "Lacey's Dapper Dasher!";
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    // gravity, pixels/s per s
    const int gravity{1'000};

    // array of colors
    Color colors[13];    // should be at least as big as numOfNebulae
    colors[0] = RAYWHITE;
    colors[1] = YELLOW;
    colors[2] = WHITE;
    colors[3] = PINK;
    colors[4] = GREEN;
    colors[5] = ORANGE;
    colors[6] = BLACK;
    colors[7] = PURPLE;
    colors[8] = BLUE;
    colors[9] = RED;
    colors[10] = DARKGRAY;
    colors[11] = LIGHTGRAY;
    colors[12] = GRAY;

    // texture 2D - scarfy player character
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimationData scarfyData;
    scarfyData.rect.width = scarfy.width/6;
    scarfyData.rect.height = scarfy.height;
    scarfyData.rect.x = 0;
    scarfyData.rect.y = 0;
    scarfyData.position.x = windowDimensions[0]/2 - scarfyData.rect.width/2;//windowWidth/2 - scarfyData.rect.width/2;
    scarfyData.position.y = windowDimensions[1] - scarfyData.rect.height;//windowHeight - scarfyData.rect.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;

    // texture 2D - nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    // animationData for nebula
    // array of type AnimationData
    AnimationData nebulae[10]{};
    int sizeOfNebulae = 10;
    for ( int i=0; i<sizeOfNebulae; i++ )
    {
        nebulae[i].rect.x = 0.0;
        nebulae[i].rect.y = 0.0;
        nebulae[i].rect.width = nebula.width/8;
        nebulae[i].rect.height = nebula.height/8;
        nebulae[i].position.x = windowDimensions[0] + (i * 300);
        nebulae[i].position.y = windowDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0;
        nebulae[i].updateTime = 1.0/16.0;
    }

    
    // nebula x velocity (pixels/second)
    int nebVelocity{-350};

    // is the character in the air
    bool isInAir{};
    // jump velocity (pixels/second(s))
    const int jumpVelocity{-600};

    int velocity{0};

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midGround = LoadTexture("textures/back-buildings.png");
    Texture2D foreGround = LoadTexture("textures/foreground.png");
    float bgX{};
    float mgX{};
    float fgX{};

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {

        // delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing
        BeginDrawing();
        ClearBackground(WHITE);

        // scroll the background
        bgX -= 20 * dT;
        if (bgX <= -background.width*2)
        {
            bgX = 0.0;
        }
        // scroll the midground
        mgX -= 40 * dT;
        if (mgX <= -midGround.width*2)
        {
            mgX = 0.0;
        }
        // scroll the foreground
        fgX -= 80 * dT;
        if (fgX <= -foreGround.width*2)
        {
            fgX = 0.0;
        }
        
        // draw the background
        Vector2 bg1Position{bgX, 0.0};
        DrawTextureEx(background, bg1Position, 0.0, 2.0, WHITE);
        Vector2 bg2Position{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Position, 0.0, 2.0, WHITE);

        // draw midGround
        Vector2 mgPosition{mgX, 0.0};
        DrawTextureEx(midGround, mgPosition, 0.0, 2.0, WHITE);
        Vector2 mg2Position{mgX + midGround.width*2, 0.0};
        DrawTextureEx(midGround, mg2Position, 0.0, 2.0, WHITE);

        // draw foreGround
        Vector2 fgPosition{fgX, 0.0};
        DrawTextureEx(foreGround, fgPosition, 0.0, 2.0, WHITE);
        Vector2 fg2Position{fgX + foreGround.width*2, 0.0};
        DrawTextureEx(foreGround, fg2Position, 0.0, 2.0, WHITE);
        

        // perform ground check
        if ( isOnGround( scarfyData, windowDimensions[1] ) )
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


        for ( int i=0; i<sizeOfNebulae; i++ )
        {
            // update nebulae position(position of each nebaula)
            nebulae[i].position.x += nebVelocity * dT;
        }

        // update position
        scarfyData.position.y += velocity * dT;

        // update scarfy animation 
        if ( !isInAir )
        {
            scarfyData = updateAnimationData(scarfyData, dT, 5);
        }

        // for loop to update the animation frame for nebulae
        for ( int i=0; i<sizeOfNebulae; i++ )
        {
            nebulae[i] = updateAnimationData(nebulae[i], dT, 7);
        }

        // draw nebulae hazards
        for ( int i=0; i<sizeOfNebulae; i++ )
        {
            DrawTextureRec(nebula, nebulae[i].rect, nebulae[i].position, colors[i]);
        }
        // draw scarfy
        DrawTextureRec(scarfy, scarfyData.rect, scarfyData.position, WHITE);

        // Basic UI/HUD
        DrawText("Level: 1", 10, 10, 20, BLUE);

        // Game Logic End
        

        // end drawing
        EndDrawing();
    }
    // clean up after run and exit
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midGround);
    UnloadTexture(foreGround);
    CloseWindow();
}