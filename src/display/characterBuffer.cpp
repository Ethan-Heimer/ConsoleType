#include <ncurses.h>
#include <vector>
#include <sstream>

#include "characterBuffer.h"
#include "display.h"

CharacterBuffer::CharacterBuffer(){
    buffer = new std::vector<Character>{};
}

CharacterBuffer::~CharacterBuffer(){
    delete buffer; 
}

void CharacterBuffer::Add(Character character){
    buffer->push_back(character);
}

void CharacterBuffer::EditColor(int index, char color){
    Character* c = &(*buffer)[index];
    c->color = color;
}

void CharacterBuffer::EditCharacter(int index, wchar_t character){
   Character* c = &(*buffer)[index];
   c->character = character;
}

void CharacterBuffer::Remove(){
    if(buffer->size() > 0)
        buffer->pop_back();
}

int CharacterBuffer::Size(){
    return buffer->size();
};

void CharacterBuffer::GetBufferIt(CharacterBuffer* buffer_ptr, BufferIt& start, BufferIt& end){
    start = buffer_ptr->buffer->begin();
    end = buffer_ptr->buffer->end();
}

int CharacterBuffer::GetBufferSize(CharacterBuffer* buffer){
    return buffer->Size();
}

std::wstring CharacterBuffer::GetBufferString(CharacterBuffer* buffer_ptr){
    std::vector<Character>* data = buffer_ptr->buffer;
    std::wstringstream stream{}; 
    
    for(auto it = data->begin(); it != data->end(); it++){
        Character c = *it;

        stream << c.character;
    }

    std::wstring str = stream.str();

    return str;
}

void CharacterBuffer::AddCharacterToBuffer(CharacterBuffer* buffer, Character character){
   buffer->Add(character); 
}

void CharacterBuffer::RemoveCharacterFromBuffer(CharacterBuffer* buffer){
    buffer->Remove();
}

void CharacterBuffer::EditCharacterColor(CharacterBuffer* buffer, int index, char Color){
    if(index >= buffer->Size())
        return;

    buffer->EditColor(index, Color);
}

void CharacterBuffer::EditCharacter(CharacterBuffer *buffer, int index, wchar_t character){
    if(index >= buffer->Size())
        return;

    buffer->EditCharacter(index, character);
}

void CharacterBuffer::EditBufferColor(CharacterBuffer *buffer, char color){
    int bufferLength = buffer->Size();

    for(int i = 0; i < bufferLength; i++){
        buffer->EditColor(i, color);
    }
}

void CharacterBuffer::EditBuffer(CharacterBuffer *buffer, const wchar_t* string){
    int bufferLength = buffer->Size();

    for(int i = 0; i < bufferLength; i++){
        buffer->EditCharacter(i, string[i]);
    }
}

//void CharacterBuffer::EditCharacterInBuffer(CharacterBuffer* buffer, int index, wchar_t character);

void CharacterBuffer::ClearBuffer(CharacterBuffer* buffer){
    buffer->buffer->clear();
}

CharacterBuffer* CharacterBuffer::CreateBuffer(){
    return new CharacterBuffer{};
}

bool CharacterBuffer::operator==(const CharacterBuffer& other){
    if(this == &other)
        return true;

    return false;
}

bool operator==(const CharacterBuffer& bufferA, const CharacterBuffer& bufferB){
    if(&bufferA == &bufferB)
        return true;

    return false;
}

bool operator==(CharacterBuffer* bufferA, const CharacterBuffer bufferB){
    return (bufferA == &bufferB); 
}
