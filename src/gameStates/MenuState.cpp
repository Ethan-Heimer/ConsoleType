#include "menuState.h" 
#include "helpState.h"
#include "debugState.h"
#include "../utils/input.h" 
#include "../utils/stringUtils.h"
#include "../utils/command.h"

#include <ncurses.h> 
#include <cstdio>
#include <sstream>
#include <vector>

void MenuState::OnEnter(){
    Display::TextBox("Console Type", "[:Help] [:Play]");

    inputBuffer = Display::CreateBuffer(); 
    inputStream = new std::wstringstream{};
}

void MenuState::WhileInState(){
   int input = Input::GetKey(); 

   if(Input::IsKeyDown(BACKSPACE))
       RemoveWCharFromWStream(inputStream);
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

        wstring errout;
        
        wstring echoCommand = L":Echo <Message>";
        wstring helpCommand = L":Help";
        wstring debugCommand = L":Debug";
 
        if(Command::Interperate(echoCommand, command, &errout) == OK){
            vector<wstring> args;
            
            if(Command::Arguments(echoCommand, command, &args, &errout) == OK)
                Display::String(L"\n"+args[0]);
        }
        else if(Command::Interperate(helpCommand, command, &errout) == OK){
            owner.ChangeState<HelpState>();
        }
        else if(Command::Interperate(debugCommand, command, &errout) == OK){
            owner.ChangeState<DebugState>();
        }
        
        if(errout != L""){
            Display::Char('\n');
            Display::TextBox(L"ERROR",errout, RED);
        }
    }
}
