#include <string>
#include <vector>

#include "../display/characterBuffer.h"

using namespace std;

class Debug{
    public:
        static void Init();

        static void Log(const char* message); 

        static const char** GetLog(int& length);

    private:
        static vector<const char*> log; 
};
