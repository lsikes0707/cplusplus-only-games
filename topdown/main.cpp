#include "raylib.h"   // import the raylib library
#include "raymath.h"    // improt the raymath library
#include "Character.h"  // import the Character class

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
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPosition{0.0, 0.0};
    const float mapScale{4.f};

    // create a variable of type Character
    Character player;
    player.setScreenPosition(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPosition = Vector2Scale(player.getWorldPosition(), -1.f);

        // draw the map with DrawTextureEx() and the player
        DrawTextureEx(map, mapPosition, 0.0, mapScale, WHITE);
        player.tick(GetFrameTime());
        // hitting the map bounds, check map bounds, stop movement
        if (player.getWorldPosition().x < 0.f ||
            player.getWorldPosition().y < 0.f ||
            player.getWorldPosition().x + windowWidth > map.width * mapScale ||
            player.getWorldPosition().y + windowHeight > map.height * mapScale)
        {
            player.undoMovement();
        }

        EndDrawing();

    }
    CloseWindow();

    // unload the map texture
    UnloadTexture(map);
    //UnloadTexture(idle);
    //UnloadTexture(run);


}