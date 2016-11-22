#include "stdafx.h"
#include "testdll.h"
#include <iostream>
#include "MainCode.h"
using namespace std;


const char* __stdcall GetIntro() {
	InitIntroduction();
	return Introduction;
}
const char* __stdcall GetName() {
	InitName();
	return Name;
}
Step __stdcall WYINPUT(struct Step requests[], struct Step responses[], int StepCount) {
	/*Step result;
	result.X0 = 0;
	result.Y0 = 0;
	result.X1 = 1;
	result.Y1 = 1;*/
	return GetNextStep(requests, responses, StepCount);
}
const void Test(int T[], int Num) 
{
	for (int i = 0; i < Num; i++) {
		cout << i << ":" << T[i] << endl;
	}
}
