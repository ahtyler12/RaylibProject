#include "StateMachine.h"

bool StateMachine::RegisterState(StateCallbacks _newCallback)
{
    Callbacks.push_back(_newCallback);
    return true;
}

StateMachine::StateMachine()
{
    StateCallbacks Standing = {.stateID = StateID::STANDING,.OnStart = Standing.OnStart, .OnUpdate = Standing.OnUpdate,.OnExit = Standing.OnExit};
    RegisterState(Standing);

   Callbacks.at(0).OnStart;
}

void StateMachine::HandleStateTransitions()
{
    for (auto callback : Callbacks)
    {
        if(callback.TriggerTransition)
        {
            //Do stuff
        }
    }
    
    
}
