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

        int Size(); 
};
