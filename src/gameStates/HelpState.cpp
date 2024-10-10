#include "helpState.h"
#include "../display/display.h"
#include "../utils/input.h"
#include <string.h>
#include "menuState.h"

void HelpState::OnEnter(){
    Display::TextBox("Help is on the way!\n[:menu] to go back");

    inputBuffer = Display::CreateBuffer();
}

void HelpState::WhileInState(){
    int input = Input::GetKey(); 

   if(Input::IsKeyDown(BACKSPACE))
       Display::Erase(1, inputBuffer);
   //else if(Input::IsKeyDown() && !Input::IsKeyDown(ENTER))
       //Display::Char(input, WHITE, inputBuffer);
 
}
void HelpState::OnExit(){
    Display::ClearAll();
    Display::DeleteBuffer(inputBuffer);
}
void HelpState::Transition(StateMachiene& owner){
    if(Input::IsKeyDown(ENTER)){
        std::wstring command = CharacterBuffer::GetBufferString(inputBuffer);

        if(command == L":Menu"){
            owner.ChangeState<MenuState>();
        }
    }
}
