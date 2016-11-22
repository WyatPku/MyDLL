#include "stdafx.h"
#include "MainCode.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
//这里是我给的demo，可以不去调用
void Wy_ProcStep(int x0, int y0, int x1, int y1, int color);
Step Wy_NextStep();

char Name[64];
char Introduction[256];
int currBotColor; // 我所执子颜色（1为黑，-1为白，棋盘状态亦同）
int gridInfo[7][7] = { 0 }; // 先x后y，记录棋盘状态

void InitName() {
	//在这里设置你的算法名称~用的人看得到哦
	strcpy_s(Name, "中英文都可以的名称");
}
void InitIntroduction() {
	//简要介绍一下你的AI吧！包括版本号啊战绩啊什么的~懒的话不写也可以的
	strcpy_s(Introduction, "简要地介绍一下你的算法，不要超过256Byte的字符都可以哦~");
}

// 从x0, y0提子，在x1, y1处落子，并模拟落子。
void ProcStep(int x0, int y0, int x1, int y1, int color)
{
	//请在这里自行完成模拟落子、改变棋盘状态的函数
	Wy_ProcStep(x0, y0, x1, y1, color);
}
Step GetNextStep(struct Step requests[], struct Step responses[], int StepCount) {
	// 初始化棋盘
	gridInfo[0][0] = gridInfo[6][6] = 1;  //|黑|白|
	gridInfo[6][0] = gridInfo[0][6] = -1; //|白|黑|
	//原本这里是读入JSON，这里不需要读入，已知有StepCount个步骤了
	// 分析自己收到的输入和自己过往的输出，并恢复状态
	int turnID = StepCount;
	cout << "Count:" << StepCount << endl;
	currBotColor = requests[0].X0 < 0 ? 1 : -1; // 第一回合收到坐标是-1, -1，说明我是黑方
	cout << "Color:" << currBotColor << endl;
	for (int i = 0; i < turnID; i++)
	{
		//cout << "requests[" << i <<"](" << requests[i].X0 << "," << 
		//	requests[i].Y0 << ")(" << requests[i].X1 << "," << requests[i].Y1  << ")" << endl;
		if (requests[i].X0 >= 0)
			ProcStep(requests[i].X0, requests[i].Y0, requests[i].X1,
				requests[i].Y1, -currBotColor); // 模拟对方落子
		if (responses[i].X0 >= 0)
			ProcStep(responses[i].X0, responses[i].Y0, responses[i].X1,
				responses[i].Y1, currBotColor); // 模拟己方落子%
	}
	//下面这段可以向控制台输出棋盘状态
	/*for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 7; i++) {
			if (gridInfo[i][j] == 0) cout << '0';
			else if (gridInfo[i][j] == 1) cout << '#';
			else if (gridInfo[i][j] == -1) cout << '.';
		}
		cout << endl;
	}*/
	// 找出合法落子点并做出决策
	int startX, startY, resultX, resultY;
	//进行决策，得出落子坐标，并赋值给上述变量
	//在这里添加你的代码

	//我的demo，从这里到下一个注释可以DIY
	Step re = Wy_NextStep();
	startX = re.X0;
	startY = re.Y0;
	resultX = re.X1;
	resultY = re.Y1;
	//以上部分是demo，可以删掉重写


	// 决策结束，输出结果
	Step goStep;
	goStep.X0 = startX;
	goStep.Y0 = startY;
	goStep.X1 = resultX;
	goStep.Y1 = resultY;
	cout << "Go" << startX << " " << startY << " " << resultX << " " << resultY << endl;
	return goStep;
}

void Wy_ProcStep(int x0, int y0, int x1, int y1, int color)
{
	if (abs(x0 - x1) > 1 || abs(y0 - y1) > 1) {
		//即跳过一个棋子，原来位置棋子消失
		gridInfo[x0][y0] = 0;
	}
	gridInfo[x1][y1] = color;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x1 + i < 0 || x1 + i > 6 || y1 + j < 0 || y1 + j > 6) continue;
			if (gridInfo[x1 + i][y1 + j] != 0) {
				gridInfo[x1 + i][y1 + j] = color;
			}
		}
	}
}
Step Wy_NextStep()
{
	vector<Step> DiffCanGo; //找到所有的结果不相同的行走方式
							//先找到走临近的。这时候应该对所有空位寻找，因为是复制，怎么走都是一样的
	for (int i = 0; i<7; i++)
	{
		for (int j = 0; j<7; j++)
		{
			if (gridInfo[i][j] == 0)
			{
				//是空的
				for (int k = -1; k<2; k++)
				{
					for (int l = -1; l<2; l++)
					{
						if (i + k < 0 || i + k > 6 || j + l < 0 || j + l > 6) continue;
						if (gridInfo[i + k][j + l] == currBotColor)
						{
							Step Go;
							Go.X0 = i + k;
							Go.Y0 = j + l;
							Go.X1 = i;
							Go.Y1 = j;
							DiffCanGo.push_back(Go);
							//找到可以走的了，要下一步就退出，不然就是重复的
							k = 3;
							l = 3;
						}
					}
				}
			}
		}
	}
	//后找走隔一个的，寻找跟自己颜色匹配的，因为是剪切，肯定寻找的方法也不一样
	for (int i = 0; i<7; i++)
	{
		for (int j = 0; j<7; j++)
		{
			if (gridInfo[i][j] == currBotColor)
			{
				//是本色棋
				for (int k = -2; k < 3; k++)
				{
					for (int l = -2; l < 3; l++)
					{
						if (i + k < 0 || i + k > 6 || j + l < 0 || j + l > 6) continue;
						//要至少有一个距离是2，才是外围一圈
						if (!(abs(k) == 2 || abs(l) == 2)) continue;
						if (gridInfo[i + k][j + l] == 0)
						{
							Step Go;
							Go.X0 = i;
							Go.Y0 = j;
							Go.X1 = i + k;
							Go.Y1 = j + l;
							DiffCanGo.push_back(Go);
						}
					}
				}
			}
		}
	}
	cout << "Size:" << DiffCanGo.size() << endl;
	for (int i = 0; i < DiffCanGo.size(); i++) {
		cout << "Cango:" << DiffCanGo.at(i).X0 << ' ' <<
			DiffCanGo.at(i).Y0 << ' ' << DiffCanGo.at(i).X1 << ' ' <<
			DiffCanGo.at(i).Y1 << endl;
	}
	int Change = -1;
	int TargetIndex = 0;
	for (int index=0; index<DiffCanGo.size(); index++)
	{
		if (abs(DiffCanGo.at(index).X0 - DiffCanGo.at(index).X1) == 2 ||
			abs(DiffCanGo.at(index).Y0 - DiffCanGo.at(index).Y1) == 2)
		{
			//是两步
			int Sum = 0;
			for (int i = -1; i<2; i++)
			{
				for (int j = -1; j<2; j++)
				{
					if (!(DiffCanGo.at(index).X1 + i<0 || DiffCanGo.at(index).X1 + i>6 ||
						DiffCanGo.at(index).Y1 + j<0 || DiffCanGo.at(index).Y1 + j>6)) {
						if (gridInfo[DiffCanGo.at(index).X1 + i][DiffCanGo.at(index).Y1 + j] ==
							-currBotColor) Sum++;
					}
				}
			}
			if (Sum > Change)
			{
				TargetIndex = index;
				Change = Sum;
			}
		}
		else
		{
			//走一步
			int Sum = 1;
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if (!(DiffCanGo.at(index).X1 + i<0 || DiffCanGo.at(index).X1 + i>6 ||
						DiffCanGo.at(index).Y1 + j<0 || DiffCanGo.at(index).Y1 + j>6)) {
						if (gridInfo[DiffCanGo.at(index).X1 + i][DiffCanGo.at(index).Y1 + j] ==
							-currBotColor) Sum++;
					}
				}
			}
			if (Sum > Change)
			{
				TargetIndex = index;
				Change = Sum;
			}
		}
	}
	return DiffCanGo.at(TargetIndex);
}
