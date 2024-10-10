#include "stateMachiene.h"
#include "../display/display.h"

StateMachiene::StateMachiene() : currentState(nullptr){}

StateMachiene::~StateMachiene(){
    currentState = nullptr;
}

void StateMachiene::InvokeCurrentState(){
    if(currentState == nullptr)
        return;
     
    currentState->WhileInState();
    currentState->Transition(*this);
}


