#include "raylib.h"
#include "CommonStates.h"
#include <vector>
#include <iostream>
#include <string>

#pragma once

 typedef bool (*StateTransition)(void*);//Event Callback declaration

enum StateID : __int32
{
    STANDING,
    CROUCHING,
    JUMPING,
    ATTACKING,
    SPECIAL,
    REACTION,
    LAUNCHREACTION,
    GUARDREACTION,
    GRABREACTION

};

struct StateCallbacks
{
    StateID stateID;
    StateTransition OnStart;
    StateTransition OnUpdate;
    StateTransition OnExit;
    StateTransition TriggerTransition;
};

class StateMachine
{
    public:
    StateMachine();
    StateID currentState = {}; //Make sure we don't have a garbage value
    void HandleStateTransitions(); //

    private:
    std::vector<StateCallbacks> Callbacks;
    bool RegisterState(StateCallbacks _newCallback); //May need to return a bool if the state was unable to be added
    
    
};