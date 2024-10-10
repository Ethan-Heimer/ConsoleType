#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <ios>
#include <ncurses.h>
#include <ncursesw/ncurses.h>
#include <sstream>
#include <string.h>
#include <string>
#include <strings.h>
#include <algorithm>
#include <cmath>

#include "display.h"
#include "characterBuffer.h"
#include "../utils/debug.h"

#define MAINBUFFER Display::GetBuffer(0)

using namespace std;

vector<CharacterBuffer*> Display::buffers = vector<CharacterBuffer*>();

void Display::Init(){
    start_color();

    init_pair(BLACK, COLOR_BLACK, 0);
    init_pair(WHITE, COLOR_WHITE, 0);
    init_pair(RED, COLOR_RED, 0);
    init_pair(BLUE, COLOR_BLUE, 0);
    init_pair(YELLOW, COLOR_YELLOW, 0);
    init_pair(GREEN, COLOR_GREEN, 0);
    init_pair(CYAN, COLOR_CYAN, 0); 
    init_pair(MAGENTA, COLOR_MAGENTA, 0);

    CreateBuffer();
}

void Display::TextBox(std::string message){
    TextBox("", message);
}

void Display::TextBox(std::string heading, std::string message){
    TextBox(heading, message, WHITE);
}

void Display::TextBox(std::string heading, std::string message, char color){
    TextBox(heading, message, color, MAINBUFFER);
}

void Display::TextBox(std::string heading, std::string message, char color, CharacterBuffer* buffer){
    wstring wheading = ConvertStringToWString(heading);
    wstring wmessage = ConvertStringToWString(message);

    TextBox(wheading, wmessage, color, buffer);
}

void Display::TextBox(wstring message){
    TextBox(L"", message);
}

void Display::TextBox(wstring heading, wstring message){
    TextBox(heading, message, WHITE);
}

void Display::TextBox(wstring heading, wstring message, char color){
    TextBox(heading, message, color, MAINBUFFER);
}

void Display::TextBox(wstring heading, wstring message, char color, CharacterBuffer *buffer){
     vector<wstring> lines;

     wstring temp;
     for(int i = 0; i < message.length(); i++){
         if(message[i] == L'\n'){
             lines.push_back(temp);
             temp = L"";
         } else
             temp += message[i];
     }

     lines.push_back(temp);

    RenderTextBox(heading, &lines[0], lines.size(), color, buffer);  
}

void Display::Header(string heading, int length, char character){
    Header(heading, length, character, WHITE);
}

void Display::Header(string heading, int length, char character, char color){
    Header(heading, length, character, color, MAINBUFFER);
}

void Display::Header(string heading, int length, char character, char color, CharacterBuffer* buffer){
    const wchar_t wcharacter = ConvertCharToWChar(character);
    const wstring wheading = ConvertStringToWString(heading);

    Header(wheading, length, wcharacter, color, buffer);
}
void Display::Header(wstring heading, int length, wchar_t character){
    Header(heading, length, character, WHITE, MAINBUFFER);
}

void Display::Header(wstring heading, int length, wchar_t character, char color, CharacterBuffer* buffer){
    int messageLen = heading.length();
    
    if(length < messageLen)
        return;

    int difference = length - messageLen;
    float padding = float(difference)/2;

    int leftPad = floor(padding);
    int rightPad = ceil(padding);

    Line(character, leftPad, color, buffer);
    String(heading, color, buffer);
    Line(character, rightPad, color, buffer);
}

void Display::Line(char character, int length){
    Line(character, length, WHITE);
}

void Display::Line(char character, int length, char color){
    Line(character, length, color, MAINBUFFER);
}

void Display::Line(char character, int length, char color, CharacterBuffer* bufferId){
    wchar_t c = ConvertCharToWChar(character);
    Line(c, length, color, bufferId); 
}

void Display::Line(wchar_t character, int length){
    Line(character, length, WHITE);
}

void Display::Line(wchar_t character, int length, char color){
    Line(character, length, color, MAINBUFFER);
}

void Display::Line(wchar_t character, int length, char color, CharacterBuffer* bufferId){
    for(int i = 0; i < length; i++){
        Char(character, color, bufferId);
    }
}

void Display::String(string string){
    String(string, WHITE);
}

void Display::String(string string, char color){
    String(string, color, MAINBUFFER);
}

void Display::String(string string, char color, CharacterBuffer* buffer){
    wstring wstring = ConvertStringToWString(string); 
    String(wstring, color, buffer);
}

void Display::String(wstring string){
    String(string, WHITE);
}

void Display::String(wstring string, char color){
    String(string, color, MAINBUFFER);
}

void Display::String(wstring string, char color, CharacterBuffer* buffer){
    int length = string.length();

    for(int i = 0; i < length; i++){
        Char(string[i], color, buffer);
    }
}

void Display::Char(char character){
    Char(character, WHITE);
}

void Display::Char(char character, char color){
    Char(character, color, MAINBUFFER);
}

void Display::Char(char character, char color, CharacterBuffer* buffer){
    wchar_t c = ConvertCharToWChar(character);
    Char(c, color, buffer);
}

void Display::Char(wchar_t character){
    Char(character, WHITE);
}

void Display::Char(wchar_t character, char color){
    Char(character, color, MAINBUFFER);
}

void Display::Char(wchar_t character, char color, CharacterBuffer* buffer){
    CharacterBuffer::AddCharacterToBuffer(buffer, {character, color});
}

void Display::Erase(int amount){
    Erase(amount, MAINBUFFER);
}

void Display::Erase(int amount, CharacterBuffer* buffer){
    for(int i = 0; i < amount; i++)
        CharacterBuffer::RemoveCharacterFromBuffer(buffer);
}

void Display::ClearAll(){
    for(auto buffer : buffers){
        Clear(buffer);
    }
}

void Display::Clear(){
    Clear(MAINBUFFER);
}

void Display::Clear(CharacterBuffer* buffer){
    CharacterBuffer::ClearBuffer(buffer);
}

CharacterBuffer* Display::CreateBuffer(){
    CharacterBuffer* buffer = CharacterBuffer::CreateBuffer();
    buffers.push_back(buffer);

    return buffer;
}

void Display::DeleteBuffer(CharacterBuffer* buffer){
    buffers.erase(remove(buffers.begin(), buffers.end(), buffer), buffers.end());
    delete buffer;
}

void Display::Show(){
    erase();

    BufferIt start;
    BufferIt end;

    cchar_t ptr;

    for(int i = 0; i < buffers.size(); i++){
        auto buffer = GetBuffer(i);
        CharacterBuffer::GetBufferIt(buffer, start, end);

        for(BufferIt it = start; it != end; it++){
            Character c = *it;

            wchar_t wchar = c.character;
            setcchar(&ptr, &wchar, 0, 0, nullptr);

            attron(COLOR_PAIR(c.color));
            add_wch(&ptr);
            attron(COLOR_PAIR(c.color));
        }
    } 
    
    refresh();
}

void Display::RenderTextBox(wstring heading, wstring* lines, int lineCount, char color, CharacterBuffer* buffer){
    int boxlen = 0;
    
    boxlen = GetLongestStringLength(lines, lineCount);
    int headLen = heading.length();

    if(headLen > boxlen)
        boxlen = headLen;

    Char(L'┌', color, buffer);
    Header(heading, boxlen, L'─', color, buffer);
    Char(L'┐', color, buffer);
    Char('\n', color, buffer);

    for(int i = 0; i < lineCount; i++){    
        int linelen = lines[i].length();
        int lineDifference = boxlen - linelen; 

        float padding = float(lineDifference) / 2.0;

        int leftPad = floor(padding);
        int rightPad = ceil(padding);
        
        Char(L'│', color, buffer);

        for(int i = 0; i < leftPad; i++)
            Char(' ', color, buffer);

        String(lines[i].c_str(), color, buffer);

        for(int i = 0; i < rightPad; i++)
            Char(' ', color, buffer);

        Char(L'│', color, buffer);
        Char('\n', color, buffer);
    }

    Char(L'└', color, buffer); 
    Line(L'─', boxlen, color, buffer);
    Char(L'┘', color, buffer);  

    Char('\n', color, buffer);
}

int Display::GetLongestStringLength(wstring* lines, int lineCount){
    int stringLength = 0;
    int maxLength = 0;

    for(int i = 0; i < lineCount; i++){
        stringLength = lines[i].length();

        if(stringLength > maxLength)
            maxLength = stringLength;
    }

    return maxLength;
}

CharacterBuffer* Display::GetBuffer(unsigned int index){
   return buffers[index]; 
}

wchar_t Display::ConvertCharToWChar(char character){
   char str[2] = {character, '\0'}; 
   
   wchar_t wchar[strlen(str)];
   mbstowcs(wchar, str, sizeof(wchar));
   
   return wchar[0];
}

wstring Display::ConvertStringToWString(string string){
    std::wstring temp(string.length(),L' ');
    std::copy(string.begin(), string.end(), temp.begin());
    return temp; 
}
