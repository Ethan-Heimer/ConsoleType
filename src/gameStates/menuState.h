#include "../utils/stateMachiene.h"
#include "../display/display.h"
#include "sstream"

class MenuState : public IState{
    public:
        void OnEnter();
        void OnExit();
        void WhileInState();
        void Transition(StateMachiene& owner);

        CharacterBuffer* inputBuffer = nullptr;
        std::wstringstream* inputStream{};
};
