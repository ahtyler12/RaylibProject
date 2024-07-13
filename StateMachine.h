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



class StateMachine
{
    
};