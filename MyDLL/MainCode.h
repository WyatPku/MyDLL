#pragma once
extern char Name[64];
extern char Introduction[256];
extern void InitName();
extern void InitIntroduction();
extern struct Step
{
	int X0; //Ҫ�ƶ������ӵ�X����
	int Y0; //Ҫ�ƶ������ӵ�Y����
	int X1; //Ҫ�ƶ�����λ��X����
	int Y1; //Ҫ�ƶ�����λ��Y����
};
extern Step GetNextStep(struct Step requests[], struct Step responses[], int StepCount);