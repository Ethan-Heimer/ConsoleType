#include <ncurses.h>
#include "input.h"

int Input::input = 0;

void Input::PollInput(){
   input = getch(); 
}

bool Input::IsKeyDown(){
    return !IsKeyDown(NO_INPUT);
}

bool Input::IsKeyDown(int key){
   return input == key; 
}

int Input::GetKey(){
    return input;
}
