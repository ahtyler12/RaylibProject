#include "raylib.h"
#include <iostream>
#include <string>

#pragma once

 typedef bool (*StateTransition)(void*);//Event Callback declaration

enum CombatStateID : __int32
{
    STANDING,
    CROUCHING,
    JUMPING,
    ATTACK,
    SPECIAL,
    REACTION,
    LAUNCHREACTION,
    GUARDREACTION,
    GRABREACTION

};


struct CombatStateContext
{
    bool bTransition = false;
    CombatStateID NextState = CombatStateID::STANDING;
    //Add Input data here

    void TransitionToState(CombatStateID StateID)
    {
        bTransition = true;
        NextState = StateID;
    }

};



class StateMachine
{
    
};