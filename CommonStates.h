#include "raylib.h"

 #pragma once

 typedef bool (*StateTransition)(void*);//Event Callback declaration

 struct CommonStatesCallbacks
 {
    StateTransition Onstart;
    StateTransition OnEnd;
    StateTransition OnUpdate;
 };

 class CommonStates
 {

 };
 

 
 