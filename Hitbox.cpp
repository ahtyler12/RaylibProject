#include "Hitbox.h"

Hitbox::Hitbox(float _width, float _height, Vector3 _position, Vector3 _size)
{
    width = _width;
    height = _height;
    position = _position;
    size = _size;
}

void Hitbox::Update()
{
    collisionBox = 
    {
        {
             position.x - size.x/2, position.y - size.y/2, position.z - size.z/2
        },
        {
            position.x + size.x/2, position.y + size.y/2, position.z + size.z/2
        }

    };
}

void Hitbox::Draw()
{
    DrawCube(position, width, height, .1f, RED);
}