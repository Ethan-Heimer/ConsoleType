#include "helpState.h"
#include "../display/display.h"
#include "../utils/input.h"
#include "../utils/stringUtils.h"
#include "../utils/command.h"
#include <string.h>
#include "menuState.h"

void HelpState::OnEnter(){
    Display::TextBox("Help is on the way!\n[:Henu] to go back");

    inputBuffer = Display::CreateBuffer();
    inputStream = new std::wstringstream{};
}

void HelpState::WhileInState(){
    int input = Input::GetKey(); 

   if(Input::IsKeyDown(BACKSPACE))
       RemoveWCharFromWStream(inputStream);
   else if(Input::IsKeyDown() && !Input::IsKeyDown(ENTER))
       *inputStream << wchar_t(input); 

   Display::Clear(inputBuffer);
   Display::TextBox(L"Command Line", inputStream->str(), WHITE, inputBuffer); 
}
void HelpState::OnExit(){
    Display::ClearAll();
    Display::DeleteBuffer(inputBuffer);

    inputStream->clear();
    delete inputStream;
}

void HelpState::Transition(StateMachiene& owner){
    if(Input::IsKeyDown(ENTER)){
        std::wstring command = inputStream->str();

        wstring errout;
        wstring menuCommand = L":Menu";

        if(Command::Interperate(menuCommand, command, &errout) == OK){
            owner.ChangeState<MenuState>();
        }

        if(errout != L""){
            Display::Char('\n');
            Display::TextBox(L"ERROR",errout, RED);
        }
    }
}
