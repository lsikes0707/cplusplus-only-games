#include "raylib.h"
#include "raymath.h"

// Character class
class Character
{
public:
    Vector2 getWorldPosition() { return worldPosition; }    // getter method
    void setScreenPosition(int winWidth, int winHeight);
    void tick(float deltaTime);
    
private:
    // Character members
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};;
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};;
    Vector2 screenPosition{};
    Vector2 worldPosition{};
    // 1: facing right, -1: facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f/12.f};   // update 12 times per second
    float speed{4.f};
    float width{};
    float height{};
};
