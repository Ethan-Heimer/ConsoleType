#include <functional>
#include <string>

using namespace std;
using CallBack = function<void()>;

class CommandLine{
    public:
        CommandLine();
        ~CommandLine();

        void AddCommand(string name, CallBack command);

    private:
};
