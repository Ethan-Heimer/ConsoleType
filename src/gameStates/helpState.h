#include "../utils/stateMachiene.h"
#include "../display/display.h"

class HelpState : public IState{
    public:
        void OnEnter();
        void OnExit();
        void WhileInState();
        void Transition(StateMachiene& owner);

    public: 
        CharacterBuffer* inputBuffer = nullptr;
};
