#include "CPPServer.h"
#include <iostream>

double CPPServer::add(double a, double b)
{
	std::cout << "CPPServer::add" << std::endl;
	return a + b;
}

double CPPServer::subtract(double a, double b)
{
	return a - b;
}
double CPPServer::multiply(double a, double b)
{
	return a * b;
}

double CPPServer::divide(double a, double b)
{
	return a / b;
}


CPPServerInterface* CreateCPPServer()
{
	return new CPPServer();
}