#include "raylib.h"

class Hitbox
{
    public:
    
    float width, height;
    Vector3 position, size;
    BoundingBox collisionBox;
    Hitbox(float _width, float _height, Vector3 _position, Vector3 _size);
    void Update();
    void Draw();
};