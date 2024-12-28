#include "raylib.h"   // import the raylib library
#include "raymath.h"    // improt the raymath library

/*
  * Program Name: Clashy Clash
  Summary: Top down, Zelda-like game
  Author: Lacey Gruwell (with guidance from GameDev.tv, c++ sharpening my c++ skills)
*/

int main()
{
    // window dimensions
    //double windowDimensions[2];
    const int windowWidth{384};  // window width
    const int windowHeight{384};  // window height
    const char * windowTitle = "Lacey's Clashy Clash";
    // initialize the window
    InitWindow(windowWidth, windowHeight, windowTitle);

    // load the map texture
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPosition{0.0, 0.0};
    float speed{4.0};

    // player
    Texture2D player = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 playerPosition{
        (float)windowWidth/2.0f - 4.0f * (0.5f * (float)player.width/6.0f),    // c-style cast
        (float)windowHeight/2.0f - 4.0f * (0.5f * (float)player.height)
    };

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) { direction.x -= 1.0; }   // move direction left
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) { direction.x += 1.0; }   // move direction right
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) { direction.y -= 1.0; }   // move direction up
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) { direction.y += 1.0; }   // move direction down
        if (Vector2Length(direction) != 0.0)
        {
            // set mapPosition = mapPosition - direction
            
            mapPosition = Vector2Subtract(mapPosition, Vector2Scale(Vector2Normalize(direction), speed));
        }


        // draw the map with DrawTextureEx()
        DrawTextureEx(map, mapPosition, 0.0, 1.0, WHITE);

        // draw the player
        Rectangle source{0.f, 0.f, (float)player.width/6.f, (float)player.height};
        Rectangle dest{playerPosition.x, playerPosition.y, 2.0f * (float)player.width/6.0f, 2.0f * (float)player.height};
        Vector2 origin{};
        DrawTexturePro(player, source, dest, origin, 0.f, WHITE);

        EndDrawing();

    }
    CloseWindow();

    // unload the map texture
    UnloadTexture(map);


}