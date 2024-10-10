#pragma once

class StateMachiene;

class IState{
    public:
        ~IState(){}

        virtual void OnEnter() = 0;
        virtual void WhileInState() = 0;
        virtual void Transition(StateMachiene& owner) = 0;
        virtual void OnExit() = 0;
};

class StateMachiene{
    public:
        StateMachiene();
        ~StateMachiene();
        
        void InvokeCurrentState();
        
        template<typename  T>
        void ChangeState (){
            if(currentState != nullptr){
                currentState->OnExit();
                delete currentState;
            }

            currentState = new T();
            currentState->OnEnter();
        }

    private:
        IState* currentState;
};
