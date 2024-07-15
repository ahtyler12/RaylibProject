#include "Entity.h"


Entity::Entity()
{
    currentMeter = maxMeter;
    currentHealth = maxHealth;
    entityModel = LoadModel("Eve.glb"); //Should have a variable for the path so that every entity can load it's own model
    //entityAnimations = LoadModelAnimations("Eve.glb", &entityAnimCount);
    animIndex = 1;
    rotationAngle = 90.f;
    rotationAxis =  {1.f, 0.f,0.f};
    scale = {1.f,1.f,1.f};
    debug = true;
    comboCounter = 0;
    inputBuffer.resize(INPUT_BUFFER_SIZE);
    hurtBoxes.resize(3); 
    velocity = {0};
    screenPosition = {0};
    otherEntity = nullptr;
    animIndex = 0;
    jumpVelocity = 25.f;
    hitStopFrames = 0;
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
        case  InputTypes::FORWARD:
        {             
            Pressed = currentInput.forward && !lastInput.forward;
            break;
        }
        case  InputTypes::BACKWARD:
        {             
            Pressed = currentInput.backward && !lastInput.backward;
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
        case  InputTypes::FORWARD:
        {             
            Pressed = currentInput.forward && !lastInput.forward;
            break;
        }
        case  InputTypes::BACKWARD:
        {             
            Pressed = currentInput.backward && !lastInput.backward;
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

void Entity::HandleHitEvent(HitEvent _event)
{
    if(hitStopFrames == 0){hitStopFrames = _event.hitStop;}
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
    //DrawModelEx(entityModel, position, rotationAxis, rotationAngle, scale, WHITE);
    if(debug)
    {
        DrawCubeWires(position, 10.f, 10.f, .1f, YELLOW);
        //Visual representation of the pushbox for debuging purposes
        DrawBoundingBox(pushBox, GREEN);
        for(auto box : hurtBoxes)
        {
            DrawBoundingBox(box, BLUE);
        }
    }
}

void Entity::Update()
{
    UpdatePhysics();
    stateMachine.HandleStateTransitions();
    //PlayAnimation(entityAnimations[animIndex]);
    
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
    if(hitStopFrames > 0)
    {
        std::cout << "In hitstop for:" << hitStopFrames << " frames!!!"<< std::endl;
        hitStopFrames-=1;
    }
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
        velocity.y -= 2; //Should be a variable rather than a literal. 
    }

    position =  {position.x + velocity.x, position.y + velocity.y, position.z + velocity.z};
    pushBox = {(Vector3){position.x - 15, position.y, position.z},(Vector3){position.x + 15, position.y + 100, position.z}}; //Update the position of the push box
    hurtBoxes.at(0) = {(Vector3){position.x - 25, position.y, position.z},(Vector3){position.x + 25, position.y + 50, position.z}};
    hurtBoxes.at(1) = {(Vector3){position.x - 25, position.y+50, position.z},(Vector3){position.x + 25, position.y + 100, position.z}};
    hurtBoxes.at(2) = {(Vector3){position.x - 25, position.y+100, position.z},(Vector3){position.x + 25, position.y + 125, position.z}};

    //Ensure that the player never goes below the "Floor" of the level. 
    if(position.y < 0)
    {
        position.y = 0;
        velocity.y = 0;
    }
}

void Entity::GatherInput()
{
    if(hasControl)
    {
        if(IsKeyDown(KEY_LEFT))
        {
            if(isFacingRight)
            {
                inputCommand.backward = true;
            }
            else
            {
                inputCommand.forward = true;
            }
            
            velocity.x -= 2;
        }
        else if(IsKeyDown(KEY_RIGHT))
        {
            if(isFacingRight)
            {
                inputCommand.forward = true;
            }
            else
            {
                inputCommand.backward = true;
            }
            velocity.x += 2;
           
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
            BoundingBox attackBox = {(Vector3){position.x + 50, position.y, position.z},(Vector3){position.x + 50, position.y + 100, position.z}}; //For testing out damage
            
            for(int i = 0; i < otherEntity->hurtBoxes.size(); i++)
            {
                if( CheckCollisionBoxes(otherEntity->hurtBoxes[i], attackBox))
                {
                    HitEvent testEvent;               
                    testEvent.hitStop = 5;
                    otherEntity->HandleHitEvent(testEvent);
                    break; /*If only one of the hurtboxes collide with the attack box then don't allow it to hit more than once*/
                }  
            }
            
        }
    }
    
}
