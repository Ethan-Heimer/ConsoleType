#include "command.h"
#include "../utils/stringUtils.h"
#include <complex>
#include <sstream>
#include <string.h>
#include <algorithm>
#include <string>
#include "../display/display.h"


//:command <arg> <arg> <arg>
CommandStatus Command::Interperate(wstring format, const wstring& command, wstring* err){
    wstring delimiter = L" ";

    vector<wstring> formatTokens = Split(format, delimiter);
    vector<wstring> commandTokens = Split(command, delimiter);

    if(formatTokens[0] == commandTokens[0]){
        *err = L"";

        return CommandStatus::OK;
    } else if(err != nullptr) {
        wstringstream errorstream;

        errorstream << "Command ";
        errorstream << commandTokens[0];
        errorstream << " is not a defined command";

        *err = errorstream.str();
    }
    return CommandStatus::ERROR;
}

CommandStatus Command::Arguments(wstring format, const wstring &command, vector<wstring>* args, wstring* err){
    wstringstream errorstream;
    
    wstring delimiter = L" ";
    
    vector<wstring> formatTokens = Split(format, delimiter);
    vector<wstring> commandTokens = Split(command, delimiter); 

    if(formatTokens.size() != commandTokens.size() && err != nullptr){
        errorstream.str(L"");

        errorstream << "Incorect Arguments: Expected ";
        errorstream << formatTokens.size() - 1;
        errorstream << " got ";
        errorstream << commandTokens.size() - 1;
        //errorstream << command;
        *err = errorstream.str(); 

        return CommandStatus::ERROR;
    }
    
    args->clear();
    for(int i = 0; i < commandTokens.size()-1; i++){
        //Display::String(L"\n"+commandTokens[i+1], RED);
        args->push_back(commandTokens[i+1]);
    }

    return (CommandStatus::OK);
}
/*CommandStatus Command::Interperate(wstring format, wstring& command, wstring* args, int& argc, wstring* err){
    wstringstream errorstream;

    wstring delimiter = L" ";

    vector<wstring> formatTokens = Split(format, delimiter);
    vector<wstring> commandTokens = Split(command, delimiter);

    if(formatTokens[0] == commandTokens[0]){

        if(formatTokens.size() != commandTokens.size() && err != nullptr){
            errorstream.str(L"");

            errorstream << "Incorect Arguments: Expected ";
            errorstream << formatTokens.size() - 1;
            errorstream << " got ";
            errorstream << commandTokens.size() - 1;

            *err = errorstream.str(); 

            return CommandStatus::ERROR;
        }

        argc = commandTokens.size() - 1;

        args = new wstring[argc];

        for(int i = 0; i < argc; i++){
            wstring w = commandTokens[i+1];
            std::copy(w.begin(), w.end(), args[i]);
        }

        return CommandStatus::OK;
    } else if(err != nullptr) {
        errorstream.str(L"");

        errorstream << "Command ";
        errorstream << commandTokens[0];
        errorstream << " is not a defined command";

        *err = errorstream.str();
    }
    return CommandStatus::ERROR;
}*/
