#include "stringUtils.h"

#include <cstring>
#include <sstream>

void RemoveCharFromSStream(stringstream& stream){
    string str = stream.str();

    if(str.length() > 0)
        str.pop_back();

    stream.str(str);
}

void RemoveWCharFromWStream(wstringstream& stream){
    wstring str = stream.str();

    if(str.length() > 0)
        str.pop_back();

    stream.str(str);
}

wchar_t ConvertCharToWChar(char character){
   char str[2] = {character, '\0'}; 
   
   wchar_t wchar[strlen(str)];
   mbstowcs(wchar, str, sizeof(wchar));
   
   return wchar[0];
}

wstring ConvertStringToWString(string string){
    std::wstring temp(string.length(),L' ');
    std::copy(string.begin(), string.end(), temp.begin());
    return temp; 
}
