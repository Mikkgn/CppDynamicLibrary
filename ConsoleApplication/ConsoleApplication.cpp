// ConsoleApplication.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <windows.h>
#include <CppDynamicLibrary/CppDynamicLibrary.h>

using namespace std;

void StaticLoadDll();
void DynamicLoadDll();
void PrintInfo(string, string, string);
string GetFunctionValueFromDll(HINSTANCE, LPCSTR);

int main()
{
	StaticLoadDll();
	DynamicLoadDll();
	return 0;
}


void StaticLoadDll() {
	string name = GetName();
	string groupName = GetGroupName();
	PrintInfo("static", name, groupName);
}


void DynamicLoadDll() {
	HINSTANCE hinstLib;

	hinstLib = LoadLibrary(L"CppDynamicLibrary.dll");

	if (hinstLib != NULL)
	{
		string name = GetFunctionValueFromDll(hinstLib, "GetName");
		string groupName = GetFunctionValueFromDll(hinstLib, "GetGroupName");
		PrintInfo("dynamic", name, groupName);
		FreeLibrary(hinstLib);
	}
}


string GetFunctionValueFromDll(HINSTANCE hinstLib, LPCSTR lpProcName) {
	string(*function)();
	(FARPROC &)function = GetProcAddress(hinstLib, lpProcName);
	if (function != NULL)
	{
		return function();
	}
	else {
		throw runtime_error("Could not load the function : \"" + string(lpProcName) + "\"");
	}
}


void PrintInfo(string loadingType, string name, string groupName) {
	cout << "Loading type: " << loadingType << endl;
	cout << "Student name: " << name << endl;
	cout << "Student group: " << groupName << endl;
}

