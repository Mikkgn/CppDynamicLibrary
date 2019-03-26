#include <string>

using namespace std;

extern "C" __declspec(dllexport) string GetName();
extern "C" __declspec(dllexport) string GetGroupName();