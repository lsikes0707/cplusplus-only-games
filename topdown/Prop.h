#include "raylib.h"

class Prop
{
public:
    Prop(Vector2 position, Texture2D texture);
private:
    Texture2D propTexture{};
    Vector2 worldPosition{};
    float scale{4.f};
};