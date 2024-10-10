#include "debug.h"
#include <vector>

vector<const char*> Debug::log = vector<const char *>(); 

void Debug::Log(const char* message){
    log.push_back(message);
}

const char** Debug::GetLog(int& length){
    length = log.size();
    return &log[0];
}
