// CPPClient2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "..\CPPClientAndServer\CPPServer.h"


int main()
{
    
    //No need to load the dll as dll and the exe are in the same x64 folder

    CPPServerInterface* server = CreateCPPServer();
	
    double value = server->add(2,3);
    std::cout << value;
	delete server; 



}

