#include "raylib.h"   // import the raylib library

/*
  * Program Name: Clashy Clash
  Summary: Top down, Zelda-like game
  Author: Lacey Gruwell (with guidance from GameDev.tv, c++ sharpening my c++ skills)
*/

int main()
{
    // window dimensions
    double windowDimensions[2];
    windowDimensions[0] = 384;  // window width
    windowDimensions[1] = 384;  // window height
    const char * windowTitle = "Lacey's Clashy Clash";
    // initialize the window
    InitWindow(windowDimensions[0], windowDimensions[1], windowTitle);

    // load the map texture
    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);


        // draw the map with DrawTextureEx()
        Vector2 mapPosition{0.0, 0.0};
        DrawTextureEx(map, mapPosition, 0.0, 1.0, WHITE);

        EndDrawing();

    }
    CloseWindow();

    // unload the map texture
    UnloadTexture(map);


}