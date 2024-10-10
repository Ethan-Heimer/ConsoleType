#pragma once

#include <string>
#include <vector>

#include "characterBuffer.h"

#define BLACK 0
#define WHITE 1
#define RED 2
#define BLUE 3
#define YELLOW 4
#define GREEN 5
#define CYAN 6
#define MAGENTA 7

class Display{
    public: 
        static void Init();
        
        static void TextBox(std::string message);
        static void TextBox(std::string heading, std::string message);
        static void TextBox(std::string heading, std::string message, char color);
        static void TextBox(std::string heading, std::string message, char color, CharacterBuffer* buffer);

        static void TextBox(std::wstring message);
        static void TextBox(std::wstring heading, std::wstring message);
        static void TextBox(std::wstring heading, std::wstring message, char color);
        static void TextBox(std::wstring heading, std::wstring message, char color, CharacterBuffer* buffer);

        static void Header(std::string heading, int length, char character);
        static void Header(std::string heading, int length, char character, char color);
        static void Header(std::string heading, int length, char character, char color, CharacterBuffer* buffer);

        static void Header(std::wstring heading, int length, wchar_t character);
        static void Header(std::wstring heading, int length, wchar_t character, char color);
        static void Header(std::wstring heading, int length, wchar_t character, char color, CharacterBuffer* buffer);

        static void Line(char character, int length);
        static void Line(char character, int length, char color);
        static void Line(char character, int length, char color, CharacterBuffer* buffer);

        static void Line(wchar_t character, int length);
        static void Line(wchar_t character, int length, char color);
        static void Line(wchar_t character, int length, char color, CharacterBuffer* buffer);

        static void String(std::string string);
        static void String(std::string string, char color);
        static void String(std::string string, char color, CharacterBuffer* buffer);

        static void String(std::wstring string);
        static void String(std::wstring string, char color);
        static void String(std::wstring string, char color, CharacterBuffer* buffer);

        static void Char(char character);
        static void Char(char character, char color);
        static void Char(char character, char color, CharacterBuffer* buffer);

        static void Char(wchar_t character);
        static void Char(wchar_t character, char color);
        static void Char(wchar_t character, char color, CharacterBuffer* buffer); 
        
        static void Erase(int amount);
        static void Erase(int amount, CharacterBuffer* buffer);

        static void ClearAll();

        static void Clear();
        static void Clear(CharacterBuffer* buffer);

        static CharacterBuffer* CreateBuffer();
        static void DeleteBuffer(CharacterBuffer* buffer);

        static void Show();

    private:
        static std::vector<CharacterBuffer*> buffers;
        static CharacterBuffer* GetBuffer(unsigned int buffer);

        static void RenderTextBox(std::wstring heading, std::wstring* lines, int lineCount, char color, CharacterBuffer* buffer);
        static int GetLongestStringLength(std::wstring* strings, int count);

        static wchar_t ConvertCharToWChar(char character);
        static std::wstring ConvertStringToWString(std::string string);
};
