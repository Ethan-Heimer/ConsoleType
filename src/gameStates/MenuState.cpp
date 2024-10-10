#include "menuState.h" 
#include "helpState.h"
#include "debugState.h"
#include "../utils/input.h" 
#include <ncurses.h> 
#include <cstdio>
#include <string.h>

void MenuState::OnEnter(){
    Display::TextBox("Console Type", "[:Help]");

    inputBuffer = Display::CreateBuffer(); 
}

void MenuState::WhileInState(){
   int input = Input::GetKey(); 

   if(Input::IsKeyDown(BACKSPACE))
       Display::Erase(1, inputBuffer);
   else if(Input::IsKeyDown() && !Input::IsKeyDown(ENTER))
       Display::Char(char(input), WHITE, inputBuffer);
       
}

void MenuState::OnExit(){
    Display::ClearAll();

    Display::DeleteBuffer(inputBuffer);
}

void MenuState::Transition(StateMachiene& owner){
    if(Input::IsKeyDown(ENTER)){
        std::wstring command = CharacterBuffer::GetBufferString(inputBuffer);

        if(command == L":Help"){
            owner.ChangeState<HelpState>();
        } else if (command == L":Debug"){
            owner.ChangeState<DebugState>();
        }
    }
}
