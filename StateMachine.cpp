#include "StateMachine.h"

void StateMachine::RegisterState(std::shared_ptr<State> _newState, StateID _id)
{
     
    StateCallbacks _newCallback = {};
    _newCallback.stateID = _id;
    _newCallback.name = _newState->name;
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

    RegisterState(standing, StateID::STANDING);
    RegisterState(jumping, StateID::JUMPING);

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

    std::cout<<"The new Current state is "<< currentState.name << "\n";
    canTransition = true;

}

void StateMachine::UpdateState()
{
    //std::cout<< "Receiving a position of X:"<< context.position.x << " , Y: " << context.position.y << " , Z: " << context.position.y <<  "\n";
    
    currentState.OnUpdate(context);
    switch (currentState.OnTransition())
    {
    case NONE:        
        break;
    case STANDING:
        canTransition = false;
        HandleStateTransitions(STANDING);
        break;
    case JUMPING:
        canTransition = false;
        HandleStateTransitions(JUMPING);
        break;
    
    default:
        break;
    }
}
