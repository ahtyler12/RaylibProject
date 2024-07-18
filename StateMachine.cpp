#include "StateMachine.h"

void StateMachine::RegisterState(std::shared_ptr<State> _newState, StateID _id)
{
     
    StateCallbacks _newCallback = {};
    _newCallback.stateID = _id;
    _newCallback.OnStart = std::bind(State::OnStart, _newState);
    _newCallback.OnExit = std::bind(State::OnExit, _newState);
    _newCallback.OnUpdate = std::bind(State::OnUpdate, _newState, std::placeholders::_1);
    _newCallback.OnTransition = std::bind(State::TriggerTransition, _newState);

    Callbacks.push_back(_newCallback);
}


StateMachine::StateMachine()
{
    canTransition = true;
    context = {};
    auto standing = std::make_shared<Standing>();
    auto jumping = std::make_shared<Jumping>();
    auto falling = std::make_shared<Falling>();

    RegisterState(standing, StateID::STANDING);
    RegisterState(jumping, StateID::JUMPING);
    RegisterState(falling, StateID::FALLING);

    currentState = Callbacks.at(0);

    currentState.OnStart(); 

   
}

void StateMachine::HandleStateTransitions(StateID _id)
{    
    
    StateCallbacks _newCallback = {};
    for ( auto callback : Callbacks)
    {
        if (callback.stateID == _id)
        {
            _newCallback = callback;
            currentState.OnExit();

            _newCallback.OnStart();
            currentState = _newCallback;
            break;
        }
            
    }

    canTransition = true;

}

void StateMachine::UpdateState()
{
    //std::cout<< "Receiving a position of X:"<< context.position.x << " , Y: " << context.position.y << " , Z: " << context.position.y <<  "\n";
    
    currentState.OnUpdate(context);
    if(canTransition)
    {
        switch (currentState.OnTransition())
        {
            case NONE:        
                break;
            case StateID::STANDING:
                canTransition = false;
                HandleStateTransitions(STANDING);
                break;
            case StateID::JUMPING:
                canTransition = false;
                HandleStateTransitions(JUMPING);
                break;
            case StateID::FALLING:
                canTransition = false;
                HandleStateTransitions(FALLING);
                break;
            
            default:
                break;
        }
    }

}
