#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(std::string string, std::string& delimiter);
vector<wstring> Split(std::wstring string, std::wstring& delimiter);

void RemoveCharFromSStream(stringstream& stream);
void RemoveWCharFromWStream(wstringstream* stream);

wchar_t ConvertCharToWChar(char character);
wstring ConvertStringToWString(string string);

