#include "raylib.h"
#include "CommonStates.h"
#include <functional>
#include <vector>
#include <iostream>
#include <string>

#pragma once

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
    std::string name;
    std::function<void()> OnStart;
    std::function<void()> OnUpdate;
    std::function<void()> OnExit;
};




class StateMachine
{
    public:
    StateMachine();
    
    StateCallbacks currentState = {}; //Make sure we don't have a garbage value
    void HandleStateTransitions(); //

    private:
       std::vector<StateCallbacks> Callbacks;
       void RegisterState(State* _newState); //May need to return a bool if the state was unable to be added
    
    
};