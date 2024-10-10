#include <ncurses.h>
#include <locale.h>

#include "Application.h"
#include "display/display.h"
#include "utils/stateMachiene.h"
#include "gameStates/menuState.h"
#include "utils/input.h"
#include "utils/debug.h"

void Application::Init(){
    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);

    keypad(stdscr, TRUE);

    Display::Init(); 

    StateMachiene gameStateMachiene{}; 
    gameStateMachiene.ChangeState<MenuState>();

    Debug::Log("Hello World");

    while(1){
        Input::PollInput(); 
        gameStateMachiene.InvokeCurrentState();

        //if(Input::IsKeyDown(ENTER))
            //Display::DeleteBuffer(buffer);

        Display::Show();
    }
}
