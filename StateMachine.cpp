#include "StateMachine.h"

void StateMachine::RegisterState(State _newState)
{
     
    StateCallbacks _newCallback = {};
    _newCallback.OnStart = std::bind(State::OnStart, _newState);
    _newCallback.OnExit = std::bind(State::OnExit, _newState);
    _newCallback.OnUpdate = std::bind(State::OnUpdate, _newState);
    _newCallback.TriggerTransition = std::bind(State::TriggerTransition, _newState);

    Callbacks.push_back(_newCallback);
}

StateMachine::StateMachine()
{
    Standing standing = {};

    RegisterState(standing);

    currentState = Callbacks.at(0);

    currentState.OnStart(); //Seems to call the State Parent Class as opposed to the Sub class function

   
}

void StateMachine::HandleStateTransitions()
{
    StateCallbacks _newState = {};

    if(currentState.TriggerTransition())
    {
        //Do stuff
    }
    
    
}
