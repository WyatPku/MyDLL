#include "stdafx.h"
#include "testdll.h"
#include <iostream>
using namespace std;
char Name[64];
char Introduction[256];
struct Step
{
	int X0;
	int Y0;
	int X1;
	int Y1;
};
const char* __stdcall GetIntro() {
	strcpy_s(Introduction, "��Խд�Ĳ��Գ���");
	return Introduction;
}
const char* __stdcall GetName() {
	strcpy_s(Name, "��������");
	return Name;
}
Step __stdcall WYINPUT() {
	Step result;
	result.X0 = 2;
	result.Y0 = 3;
	result.X1 = 4;
	result.Y1 = 5;
	return result;
}