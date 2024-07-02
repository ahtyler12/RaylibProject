#include "Entity.h"


Entity::Entity()
{
    currentMeter = maxMeter;
    currentHealth = maxHealth;
    entityModel = LoadModel("Eve.glb"); //Should have a variable for the path so that every entity can load it's own model
    entityAnimations = LoadModelAnimations("Eve.glb", &entityAnimCount);
    animIndex = 1;
    rotationAngle = 90.f;
    rotationAxis =  {1.f, 0.f,0.f};
    scale = {1.f,1.f,1.f};
    debug = true;
    activeHitboxes.clear();
    comboCounter = 0;
    inputBuffer.resize(INPUT_BUFFER_SIZE);
    velocity = {0.f,0.f,0.f};
    otherEntity = nullptr;
    animIndex = 0;
    jumpVelocity = 25.f;
}

bool Entity::wasInputPressedOnFrame(InputTypes inputToCheck, int frame)
{
    const unsigned int _bufferIndex = frame % inputBuffer.max_size();
    const unsigned int _lastBufferIndex = (inputBuffer.max_size() + frame -1) % inputBuffer.max_size();

    const InputData currentInput = inputBuffer.at(_bufferIndex);
    const InputData lastInput = inputBuffer.at(_lastBufferIndex);

    bool Pressed =  false;
    switch (inputToCheck)
    {
        case  InputTypes::UP:
        {             
            Pressed = currentInput.up && !lastInput.up;
            break;
        }
        case  InputTypes::DOWN:
        {             
            Pressed = currentInput.down && !lastInput.down;
            break;
        }
        case  InputTypes::RIGHT:
        {             
            Pressed = currentInput.right && !lastInput.right;
            break;
        }
        case  InputTypes::LEFT:
        {             
            Pressed = currentInput.left && !lastInput.left;
            break;
        }
        case  InputTypes::ATTACK:
        {             
            Pressed = currentInput.attack && !lastInput.attack;
            break;
        }
        
        default:
        {     
            Pressed = false;
            break;
        }
    }

    return Pressed;
}

bool Entity::wasInputPressed(InputTypes inputToCheck)
{
    const InputData currentInput = GetCurrentInputCommand();
    const InputData lastInput = GetLastInputCommand();
    bool Pressed = false;

    switch (inputToCheck)
    {
        case  InputTypes::UP:
        {             
            Pressed = currentInput.up && !lastInput.up;
            break;
        }
        case  InputTypes::DOWN:
        {             
            Pressed = currentInput.down && !lastInput.down;
            break;
        }
        case  InputTypes::RIGHT:
        {             
            Pressed = currentInput.right && !lastInput.right;
            break;
        }
        case  InputTypes::LEFT:
        {             
            Pressed = currentInput.left && !lastInput.left;
            break;
        }
        case  InputTypes::ATTACK:
        {             
            Pressed = currentInput.attack && !lastInput.attack;
            break;
        }
        
        default:
        {     
            Pressed = false;
            break;
        }
    }

    return Pressed;
}

void Entity::UpdateInputs()
{
    bufferIndex = (bufferIndex +1) % inputBuffer.max_size();
}

InputData Entity::GetCurrentInputCommand()
{
    return inputBuffer.at(bufferIndex);
}

InputData Entity::GetLastInputCommand()
{
    return inputBuffer.at((inputBuffer.max_size() + bufferIndex -1) % inputBuffer.max_size());
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
    UpdatePhysics();
    PlayAnimation(entityAnimations[animIndex]);
    
}

void Entity::UpdateAnimations(unsigned int _animIndex)
{
    /*May need to make these variables globals for state machine functionality*/
    ModelAnimation currentAnim = entityAnimations[_animIndex]; //Set the current animation
    currentAnimFrame = 0;
    PlayAnimation(currentAnim);
}

void Entity::PlayAnimation(ModelAnimation anim)
{
    UpdateModelAnimation(entityModel, anim, currentAnimFrame);
    if(currentAnimFrame >= anim.frameCount)
    {
        currentAnimFrame = 0; //Should Automatically loop the animation
    }
    else
    {
        currentAnimFrame++;
    }
}

void Entity::UpdatePhysics()
{
    /*Determine if oponent is on right or left*/
    if(otherEntity != nullptr)
    {
        if(otherEntity->position.x > position.x)
        {
            isFacingRight = true;
        }
        else
        {
            isFacingRight = false;
        }
    }

    if(position.y > 0)
    {
        velocity.y -= 2;
    }

    position =  {position.x + velocity.x, position.y + velocity.y, position.z + velocity.z};
    if(position.y < 0)
    {
        position.y = 0;
        velocity.y = 0;
    }
}

void Entity::GatherInput()
{
    if(IsKeyDown(KEY_LEFT))
    {
        inputCommand.left = true;
        std::cout<<"Pressing Left!"<<std::endl;
        velocity.x -= 2;
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        velocity.x += 2;
        std::cout<<"Pressing Right!"<<std::endl;
        inputCommand.right = true;
    }
    else
    {
        velocity.x = 0;
    }

    if(IsKeyPressed(KEY_UP))
    {
        velocity.y = jumpVelocity;
    }

    if(IsKeyPressed(KEY_C))
    {
        if(scale.x > 0)
        {
            scale.x = -1;
            scale.y = -1;
        }
        else
        {
           scale.x = 1;
           scale.y = 1;
        }
    }
}
