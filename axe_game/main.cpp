// game dev (external, not standard c++) library
#include "raylib.h" 

/*
  * Axe Game
  * A game about axes???
  * Author: Lacey (while learning from GameDev.tv re:
    C++ Fundamentals: Learn Game Programming For Beginners)
*/
int main()
{
    // Window to play the game
    // Window variables
    int width = 800;  // could use bracket initalization
    int height = 450; // int height{200};
    const char * windowTitle = "Lacey's Popup!";
    // Initialize the window
    InitWindow(width, height, windowTitle);

    // Circle variables
    int circle_x = width/2;   // circle x
    int circle_y = height/2;  // circle y
    int circle_r = 25;        // cirlce radius
    Color circle_c = PURPLE;  // circle (raylib) color
    int circle_s = 5;         // circle speed
    // circle edges
    int l_circle_x{circle_x - circle_r};   // x-coord of left edge of circle
    int r_circle_x{circle_x + circle_r};  // x-coord of right edge of circle
    int u_circle_y{circle_y - circle_r};  // y-coord of upper edge of circle
    int b_circle_y{circle_y + circle_r};  // y-coord of bottom edge of circle

    
    // axe variables, using {} for fun/practice
    int axe_x{300};   // axe x
    int axe_y{0};     // axe y
    int axe_w{50};    // axe width
    int axe_h{50};    // axe height
    Color axe_c{RED}; // axe (raylib) color
    int axe_d{10};    // axe direction
    // axe edges
    int l_axe_x{axe_x};           // x-coord of left edge of axe
    int r_axe_x{axe_x + axe_w};   // x-coord of right edge of axe
    int u_axe_y{axe_y};           // y-coord of upper edge of axe
    int b_axe_y{axe_y + axe_h};   // y-coord of bottom edge of axe
    bool collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

    SetTargetFPS(60);
    while ( !WindowShouldClose() )
    {
      BeginDrawing();
      ClearBackground(WHITE);

      if ( collision_with_axe )
      {
        DrawText("Game Over!", 350, height/2, 20, RED);
      }
      else
      {
        // Game logic begins

        // Update edges
        l_circle_x = circle_x - circle_r;
        r_circle_x = circle_x + circle_r;
        u_circle_y = circle_y - circle_r;
        b_circle_y = circle_y + circle_r;
        l_axe_x = axe_x;
        r_axe_x = axe_x + axe_w;
        u_axe_y = axe_y;
        b_axe_y = axe_y + axe_h;
        // update collision_with_axe
        collision_with_axe = 
                        (b_axe_y >= u_circle_y) && 
                        (u_axe_y <= b_circle_y) && 
                        (r_axe_x >= l_circle_x) && 
                        (l_axe_x <= r_circle_x);

        DrawCircle(circle_x, circle_y, circle_r, circle_c);
        DrawRectangle(axe_x, axe_y, axe_w, axe_h, axe_c);

        // falling axe, keeping bounds (top/bottom)
        axe_y += axe_d;
        if (axe_y > height || axe_y < 0 )
        {
          axe_d = -axe_d;
        }

        // GO RIGHT, with bounds
        if ( IsKeyDown(KEY_RIGHT) && circle_x < width )
        {
          // move circle right if right key is pressed
          circle_x += circle_s;
        }
        // GO LEFT, with bounds
        if ( IsKeyDown(KEY_LEFT) && circle_x > 0 )
        {
          // move circle left if left key is pressed
          circle_x -= circle_s;
        }
        // GO UP, with bounds
        if ( IsKeyDown(KEY_UP) && circle_y > 0 )
        {
          // move circle up if up key is pressed
          circle_y -= circle_s;
        }
        // GO DOWN, with bounds
        if ( IsKeyDown(KEY_DOWN) && circle_y < height )
        {
          // move circle down if down key is pressed
          circle_y += circle_s;
        }

        // Level Text
        DrawText("Level: 1", 10, 10, 20, BLUE);
        DrawText("Don't let the            touch you!", width-345, height-35, 20, ORANGE);
        DrawText("Red Axe", width-207, height-35, 20, RED);
      }

      

      // Game logic ends
      EndDrawing();
    }

}