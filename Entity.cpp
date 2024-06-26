#include "Entity.h"

Entity::Entity()
{
    currentMeter = maxMeter;
    currentHealth = maxHealth;
    entityModel = LoadModel("Eve.glb"); //Should have a variable for the path so that every entity can load it's own model
    entityAnimations = LoadModelAnimations("Eve.glb", &entityAnimCount);
    animIndex = 1;
    position = {.0f,0.f,0.f};
    rotationAngle = 90.f;
    rotationAxis =  {1.f, 0.f,0.f};
    scale = {.01f,.01f,.01f};
    debug = true;
    activeHitboxes.clear();
    comboCounter = 0;
}

bool Entity::CheckCollision(Entity *entity)
{
    if(CheckCollisionBoxes(pushBox, entity->pushBox))
    {
        return true;
    }
    return false;
}

void Entity::Draw()
{
    DrawModelEx(entityModel, position, rotationAxis, rotationAngle, scale, WHITE);
    if(debug)
    {
        DrawCubeWires(position, 1, 1, .1f, YELLOW);
    }
}

void Entity::Update()
{
    UpdateAnimations(animIndex);
}

void Entity::UpdateAnimations(unsigned int _animIndex)
{
    /*May need to make these variables globals for state machine functionality*/
    ModelAnimation anim = entityAnimations[_animIndex]; //Set the current animation
    unsigned int currentAnimFrame = 0;
    currentAnimFrame = (currentAnimFrame +1)%anim.frameCount; //Update the current frame of animation
    UpdateModelAnimation(entityModel, anim, currentAnimFrame);
}
