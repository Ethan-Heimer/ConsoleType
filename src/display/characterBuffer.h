#pragma once

#include <vector>
#include <string>

struct Character{ 
    Character(wchar_t character, char color)
    : character(character), color(color){};
    ~Character(){};

    wchar_t character;
    char color;
};

using BufferIt = std::vector<Character>::iterator;

class CharacterBuffer{
    public: 
        static void AddCharacterToBuffer(CharacterBuffer* buffer, Character character);
        static void RemoveCharacterFromBuffer(CharacterBuffer* buffer);

        static void EditBufferColor(CharacterBuffer* buffer, char color);
        static void EditBuffer(CharacterBuffer* buffer, const wchar_t* character);

        static void EditCharacterColor(CharacterBuffer* buffer, int index, char color);
        static void EditCharacter(CharacterBuffer* buffer, int index, wchar_t character);

        static void ClearBuffer(CharacterBuffer* buffer);

        static void GetBufferIt(CharacterBuffer* buffer, BufferIt& start, BufferIt& end);
        static int GetBufferSize(CharacterBuffer* buffer);
        static std::wstring GetBufferString(CharacterBuffer* buffer);

        static CharacterBuffer* CreateBuffer();
        
        CharacterBuffer();
        ~CharacterBuffer(); 

        bool operator == (const CharacterBuffer& other);

    private:
        std::vector<Character>* buffer;

        void Add(Character character);
        void Remove();

        void EditColor(int index, char color);
        void EditCharacter(int index, wchar_t character);

        int Size(); 
};
