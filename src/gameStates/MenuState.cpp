#include "menuState.h" 
#include "helpState.h"
#include "debugState.h"
#include "../utils/input.h" 
#include "../utils/stringUtils.h"

#include <ncurses.h> 
#include <cstdio>
#include <sstream>

void MenuState::OnEnter(){
    Display::TextBox("Console Type", "[:Help]");

    inputBuffer = Display::CreateBuffer(); 
    inputStream = new std::wstringstream{};
}

void MenuState::WhileInState(){
   int input = Input::GetKey(); 

   if(Input::IsKeyDown(BACKSPACE))
       RemoveWCharFromWStream(*inputStream);
   else if(Input::IsKeyDown() && !Input::IsKeyDown(ENTER))
       *inputStream << wchar_t(input);
       
   Display::Clear(inputBuffer);
   Display::TextBox(L"Command Line", inputStream->str(), WHITE, inputBuffer);

   /* 
   if(Input::IsKeyDown() && *commandFailed == true){
       *commandFailed = false;
       CharacterBuffer::EditBufferColor(inputBuffer, WHITE);
   } else if(*commandFailed)
       CharacterBuffer::EditBufferColor(inputBuffer, RED);
   */
}

void MenuState::OnExit(){
    Display::ClearAll();
    Display::DeleteBuffer(inputBuffer);
    
    inputStream->clear();
    delete inputStream;
}

void MenuState::Transition(StateMachiene& owner){
    if(Input::IsKeyDown(ENTER)){
        std::wstring command = inputStream->str();

        if(command == L":Help"){
            owner.ChangeState<HelpState>();
        } else if (command == L":Debug"){
            owner.ChangeState<DebugState>();
        }
    }
}
