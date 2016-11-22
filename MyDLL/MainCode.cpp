#include "stdafx.h"
#include "MainCode.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
//�������Ҹ���demo�����Բ�ȥ����
void Wy_ProcStep(int x0, int y0, int x1, int y1, int color);
Step Wy_NextStep();

char Name[64];
char Introduction[256];
int currBotColor; // ����ִ����ɫ��1Ϊ�ڣ�-1Ϊ�ף�����״̬��ͬ��
int gridInfo[7][7] = { 0 }; // ��x��y����¼����״̬

void InitName() {
	//��������������㷨����~�õ��˿��õ�Ŷ
	strcpy_s(Name, "��Ӣ�Ķ����Ե�����");
}
void InitIntroduction() {
	//��Ҫ����һ�����AI�ɣ������汾�Ű�ս����ʲô��~���Ļ���дҲ���Ե�
	strcpy_s(Introduction, "��Ҫ�ؽ���һ������㷨����Ҫ����256Byte���ַ�������Ŷ~");
}

// ��x0, y0���ӣ���x1, y1�����ӣ���ģ�����ӡ�
void ProcStep(int x0, int y0, int x1, int y1, int color)
{
	//���������������ģ�����ӡ��ı�����״̬�ĺ���
	Wy_ProcStep(x0, y0, x1, y1, color);
}
Step GetNextStep(struct Step requests[], struct Step responses[], int StepCount) {
	// ��ʼ������
	gridInfo[0][0] = gridInfo[6][6] = 1;  //|��|��|
	gridInfo[6][0] = gridInfo[0][6] = -1; //|��|��|
	//ԭ�������Ƕ���JSON�����ﲻ��Ҫ���룬��֪��StepCount��������
	// �����Լ��յ���������Լ���������������ָ�״̬
	int turnID = StepCount;
	cout << "Count:" << StepCount << endl;
	currBotColor = requests[0].X0 < 0 ? 1 : -1; // ��һ�غ��յ�������-1, -1��˵�����Ǻڷ�
	cout << "Color:" << currBotColor << endl;
	for (int i = 0; i < turnID; i++)
	{
		//cout << "requests[" << i <<"](" << requests[i].X0 << "," << 
		//	requests[i].Y0 << ")(" << requests[i].X1 << "," << requests[i].Y1  << ")" << endl;
		if (requests[i].X0 >= 0)
			ProcStep(requests[i].X0, requests[i].Y0, requests[i].X1,
				requests[i].Y1, -currBotColor); // ģ��Է�����
		if (responses[i].X0 >= 0)
			ProcStep(responses[i].X0, responses[i].Y0, responses[i].X1,
				responses[i].Y1, currBotColor); // ģ�⼺������%
	}
	//������ο��������̨�������״̬
	/*for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 7; i++) {
			if (gridInfo[i][j] == 0) cout << '0';
			else if (gridInfo[i][j] == 1) cout << '#';
			else if (gridInfo[i][j] == -1) cout << '.';
		}
		cout << endl;
	}*/
	// �ҳ��Ϸ����ӵ㲢��������
	int startX, startY, resultX, resultY;
	//���о��ߣ��ó��������꣬����ֵ����������
	//������������Ĵ���

	//�ҵ�demo�������ﵽ��һ��ע�Ϳ���DIY
	Step re = Wy_NextStep();
	startX = re.X0;
	startY = re.Y0;
	resultX = re.X1;
	resultY = re.Y1;
	//���ϲ�����demo������ɾ����д


	// ���߽�����������
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
		//������һ�����ӣ�ԭ��λ��������ʧ
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
	vector<Step> DiffCanGo; //�ҵ����еĽ������ͬ�����߷�ʽ
							//���ҵ����ٽ��ġ���ʱ��Ӧ�ö����п�λѰ�ң���Ϊ�Ǹ��ƣ���ô�߶���һ����
	for (int i = 0; i<7; i++)
	{
		for (int j = 0; j<7; j++)
		{
			if (gridInfo[i][j] == 0)
			{
				//�ǿյ�
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
							//�ҵ������ߵ��ˣ�Ҫ��һ�����˳�����Ȼ�����ظ���
							k = 3;
							l = 3;
						}
					}
				}
			}
		}
	}
	//�����߸�һ���ģ�Ѱ�Ҹ��Լ���ɫƥ��ģ���Ϊ�Ǽ��У��϶�Ѱ�ҵķ���Ҳ��һ��
	for (int i = 0; i<7; i++)
	{
		for (int j = 0; j<7; j++)
		{
			if (gridInfo[i][j] == currBotColor)
			{
				//�Ǳ�ɫ��
				for (int k = -2; k < 3; k++)
				{
					for (int l = -2; l < 3; l++)
					{
						if (i + k < 0 || i + k > 6 || j + l < 0 || j + l > 6) continue;
						//Ҫ������һ��������2��������ΧһȦ
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
			//������
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
			//��һ��
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