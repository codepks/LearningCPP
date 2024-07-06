// CPPClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <tlhelp32.h>
#include <filesystem>
#include <iostream>
#include "..\CPPClientAndServer\CPPServer.h"

int main()
{
    /*
    * 1. LoadLibrary
    * 2. Import the dll in the project property
    * 3. COM
    */

    HINSTANCE hubModule = nullptr;

	hubModule = LoadLibrary(L"CPPServer.dll");

	if (hubModule == nullptr)	{
		std::cout << "Failed to load DLL" << std::endl;
	}
    else
    {
        //Create a function pointer to match the signature of the function you want to call
        typedef CPPServerInterface* (*pFunctionPtr)();
        auto pFunction = (pFunctionPtr)GetProcAddress(hubModule, "CreateCPPServer");

        CPPServerInterface* obj = pFunction();

        std::cout << obj->add(3, 4);
    }


	FreeLibrary(hubModule);


    std::cout << "Hello World!\n";
}

