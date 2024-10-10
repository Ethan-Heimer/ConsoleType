#include "debugState.h"
#include "../utils/debug.h"
#include "../display/display.h"

void DebugState::OnEnter(){ 
    Display::Header("Terminal Colors", 46, '-');
    Display::Char('\n');

    Display::String("Black ", BLACK);
    Display::String("White ", WHITE);
    Display::String("Red ", RED);
    Display::String("Blue ", BLUE);
    Display::String("Green ", GREEN);
    Display::String("Yellow ", YELLOW);
    Display::String("Cyan ", CYAN);
    Display::String("Magenta", MAGENTA);

    Display::Char('\n'); 
    Display::Line('-', 46);
    Display::Char('\n');

    Display::Header("Debug Log", 46, '-', RED);

    int count = 0;
    const char** log = Debug::GetLog(count);

    for(int i = 0; i < count; i++){
        Display::Char('\n');
        Display::String(log[i], RED);
    }

    Display::Char('\n');
    Display::Line('-', 46, RED);
}

void DebugState::WhileInState(){}

void DebugState::OnExit(){}

void DebugState::Transition(StateMachiene& owner){}
