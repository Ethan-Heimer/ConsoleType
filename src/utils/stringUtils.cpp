#include "stringUtils.h"

#include <cstring>
#include <sstream>
#include <vector>

vector<wstring> Split(wstring str, wstring& delimiter){
    vector<wstring> tokens;
    wstring token;

    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    tokens.push_back(str);
    return tokens;
}

vector<string> Split(string str, string& delimiter){
    vector<string> tokens;
    string token;

    size_t pos = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }

    tokens.push_back(str);
    return tokens;
}

void RemoveCharFromSStream(stringstream* stream){
    string str = stream->str();

    if(str.length() > 0)
        str.pop_back();

    stream->str("");

    for(int i = 0; i < str.length(); i++)
        (*stream) << str[i];
}

void RemoveWCharFromWStream(wstringstream* stream){
    wstring str = stream->str();

    if(str.length() > 0)
        str.pop_back();

    stream->str(L"");

    for(int i = 0; i < str.length(); i++)
        (*stream) << str[i];
    
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
