#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
//#include <ctime>
#include <random>
#include <chrono>    // 高精度时间种子
using namespace std;
char board[11][21];
int x = 0;
int y = 0;
void display()
{

	//system("cls");
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}
void init()
{
	for (int i = 0; i < 11; i += 2)
	{
		for (int j = 0; j < 21; j++)
		{
			board[i][j] = '-';

		}
	}
	for (int i = 1; i < 11; i += 2)
	{
		for (int j = 0; j < 21; j += 4)
		{
			board[i][j] = '|';
		}
		for (int j = 0; j < 21; j++)
		{
			if (board[i][j] != '|')
			{
				board[i][j] = ' ';
			}
		}
	}
}
int getRandomNum(int range)
{
	// 用高精度时间作为种子（避免秒级重复）
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 rng(seed);  // 梅森旋转引擎，高精度、长周期
	uniform_int_distribution<int> dist(0, range);  // 均匀分布在 [min, max]
	return dist(rng);
}
void getEntrance()
{
	int flag = getRandomNum(1);
	cout << flag << endl;
	if (flag)
	{
		if (y = getRandomNum(1))
		{
			y = 4;
			x = getRandomNum(4);
		}
		else
		{
			y = 0;
			x = getRandomNum(4);
		}
	}
	else
	{
		if (x = getRandomNum(1))
		{
			x = 4;
			y = getRandomNum(4);
		}
		else
		{
			x = 0;
			y = getRandomNum(4);
		}
	}
	x = x * 2 + 1;
	y = y * 4 + 2;
}
void updateBoard(char forward)
{
	//char tempRow[5];
	int cursor = 18;
	for (int i = 1; i <= 9; i += 2)
	{
		int cursor = 2;
		for (int j = 6; j <= 18; j += 4)
		{
			//cout << i << "行" << j << "列" << board[i][j] << "被赋值给" << ((j + 2) / 4)-1 << "列" << endl;
			//tempRow[((j + 2) / 4) - 1] = board[i][j];
			board[i][cursor] = board[i][j];
			cursor += 4;
			board[i][j] = ' ';
		}
		//cout << endl;
		//for (int j = 0; j < 5; j++)
		//{
		//	cout << tempRow[i] << ".";
		//}

		//for (int j = 4; j >= 0; j--)
		//{
		//	if (tempRow[j] != ' ')
		//	{
		//		tempRow[cursor] = tempRow[j];
		//		cursor--;
		//		tempRow[j] = ' ';
		//	}
		//}
		//cout <<endl<<"tempRow处理后" << endl;
		//for (int j = 0; j < 5; j++)
		//{
		//	cout << tempRow[i] << ".";
		//}
		//for (int j = 2; j <= 19; j += 4)
		//{
		//	board[i][j]=tempRow[((j + 2) / 4) - 1];
		//}
		//cout << endl;
		//for (int i = 0; i < 5; i++)
		//{
		//	cout << tempRow[i] << " ";
		//}
	}
}
int main()
{
	init();//初始化
	getEntrance();//获取随机入口
	cout << x << " " << y;
	board[x][y] = '2';
	cout << endl;
	display();
	char forward;
	//while (true) {
	//	cin >> forward;
	//	updateBoard(forward);
	//}
	cin >> forward;
	updateBoard(forward);
	display();

	return 0;
}
//--------------------- 
//|   |   |   |   |   |
//--------------------- 
//|   |   |   |   |   |
//--------------------- 
//|   |   |   |   |   |
//--------------------- 
//|   |   |   |   |   |
//--------------------- 
//|   |   |   |   |   |
//--------------------- 
