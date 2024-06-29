#include "raylib.h"
#include "Hitbox.h"
#include <vector>
 
enum InputTypes
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ATTACK
};

struct InputData
{   
    bool up;
    bool down;
    bool left;
    bool right;
    bool attack;

    void Reset()
    {
        up = false;
        down = false;
        left = false;
        right = false;
        attack = false;
    }
    
};


class Entity
{
    public:
    Entity();

    /*Common Variables*/
    float maxHealth = 1;
    float currentHealth;
    float maxMeter = 1;
    float currentMeter;
    float walkSpeed;
    float backWalkSpeed;
    float forwarddashDistance;
    float backdashDistance;
    Vector3 velocity;
    float jumpVelocity;
    Vector3 position;
    //Current number of jumps
    int jumpCount;
    //Actions available in the air
    int airActionsAvailable = 2;

    /*Model Related Variables*/
    Model entityModel;
    ModelAnimation *entityAnimations;
    unsigned int entityAnimCount;
    unsigned int animIndex; 
    Vector3 rotationAxis, scale /*this might be useful for flipping the model need to test more*/;
    float rotationAngle;
    bool isFacingRight;
    bool canFlip;
    bool isStuckInEnemy;

    /*May need a different method to handle this*/
    std::vector<Hitbox> activeHitboxes;

    /*Damage Related*/
    int stunFrames;
    int hitStopFrames;
    bool shouldWallBounce;
    bool shouldGroundBounce;
    bool counterHitActive;
    //Number of frames where an Instant Block is considered valid
    const int instantBlockWindow = 6;
    //Number of frames needed to pass to not get locked out of instant block
    const int ibLockOut = 10;
    //Number of frames before another instant block can be performed
    int ibCoolDown;
    //The frame to start checking for an Instant Block. -1 indicates no opportunity for instant block
    int startIBframe;
    bool shouldHardKnockdown;
    bool landedHit;
    float damageDecayModifier;
    float hitStunDecayModifier; 
    int comboCounter;

    /*Input variables*/
    int INPUT_BUFFER_SIZE = 60;
    InputData inputCommand;
    std::vector<InputData> inputBuffer;
    int bufferIndex = -1;

    //inputBuffer.resize(INPUT_BUFFER_SIZE);


    /*Reference to the other player*/
    Entity* otherEntity;

    /*Pushbox Data*/
    Vector3 size;
    BoundingBox pushBox;

    bool debug;

    bool CheckCollision(Entity* _entity);
    void Draw();
    void Update();
    void UpdateAnimations(unsigned int _animIndex);
    void UpdatePhysics();
    void GatherInput();
    bool wasInputPressedOnFrame(InputTypes inputToCheck, int frame);
    bool wasInputPressed(InputTypes inputToCheck);
    void UpdateInputs();
    InputData GetCurrentInputCommand();
    InputData GetLastInputCommand();

};