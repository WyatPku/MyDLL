#include "stdafx.h"
#include "testdll.h"
#include <iostream>
using namespace std;
struct Step
{
	int X0;
	int Y0;
	int X1;
	int Y1;
};
struct Info
{
	int x0;
	double a1;
	double a2;
};

Step __stdcall ADD(int plus1, int plus2, Info* infop)
{
	Step result;
	result.X0 = 2;
	result.Y0 = 3;
	result.X1 = plus1 + plus2 + infop->x0;
	result.Y1 = 5;
	return result;
}

Step __stdcall WYINPUT() {
	Step result;
	result.X0 = 2;
	result.Y0 = 3;
	result.X1 = 4;
	result.Y1 = 5;
	return result;
}
