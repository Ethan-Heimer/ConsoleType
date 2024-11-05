#include <complex>
#include <string>
#include <vector>

using namespace std;

enum CommandStatus{
    OK = 0,
    ERROR = 1,
};

class Command{
    public:
        static CommandStatus Interperate(wstring format, const wstring& command, wstring* err);
        static CommandStatus Arguments(wstring format, const wstring& command, vector<wstring>* args, wstring* err);
};
