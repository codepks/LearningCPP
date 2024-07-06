#pragma once

#ifdef CALCULATOR_API
#define CALCULATOR_EXPORT_API __declspec(dllexport)
#else
#define CALCULATOR_EXPORT_API __declspec(dllimport)
#endif // EXPORT_Calculator


class CALCULATOR_EXPORT_API  CPPServerInterface
{
public:
	virtual double add (double a, double b ) = 0;
	virtual double subtract (double a, double b ) = 0;
	virtual double multiply (double a, double b ) = 0;
	virtual double divide (double a, double b ) = 0;
};


class CPPServer : public CPPServerInterface
{
public:
	CPPServer() = default;
	~CPPServer() = default;


public:
	double add (double a, double b ) override;
	double subtract (double a, double b ) override;
	double multiply (double a, double b ) override;
	double divide (double a, double b ) override;

};


extern "C"
{
	CALCULATOR_EXPORT_API CPPServerInterface* CreateCPPServer();
}
