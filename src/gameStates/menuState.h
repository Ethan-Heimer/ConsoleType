#include "../utils/stateMachiene.h"
#include "../display/display.h"

class MenuState : public IState{
    public:
        void OnEnter();
        void OnExit();
        void WhileInState();
        void Transition(StateMachiene& owner);

    public: 
        CharacterBuffer* inputBuffer = nullptr;
};
