#pragma once
extern char Name[64];
extern char Introduction[256];
extern void InitName();
extern void InitIntroduction();
extern struct Step
{
	int X0; //要移动的棋子的X坐标
	int Y0; //要移动的棋子的Y坐标
	int X1; //要移动到的位置X坐标
	int Y1; //要移动到的位置Y坐标
};
extern Step GetNextStep(struct Step requests[], struct Step responses[], int StepCount);
#define AtaxxDLLDevelop
#define dllDebug
