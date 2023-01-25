// 推箱子.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<cstdio>
#include<easyx.h>
#include<cstdlib>
#include <iostream>
#include <conio.h>
using namespace std;
int map[3][10][10] = { {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,0,1,2,0,1,0,0,0},
	{0,1,1,1,3,0,1,0,0,0},
	{0,1,2,3,4,0,0,1,1,1},
	{0,1,1,1,1,3,0,3,2,1},
	{0,0,0,0,1,2,1,1,1,1},
	{0,0,0,0,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0},
	{0,1,0,2,1,1,2,0,1,0},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,3,4,3,0,0,0,1},
	{0,1,0,0,3,3,0,0,1,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,0,1,2,2,1,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
},
{
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,0,1,1,0,1,0,0},
	{0,0,0,1,0,0,1,0,0,0},
}
};
//空地0 墙1 目的地2 箱子3 玩家4 箱子目的地5 玩家目的地6
enum Mine
{
	SPACE,//空地
	WALL,//墙
	DEST,//目的地
	BOX,//箱子
	PLAYER
};
//确定当前是哪一关
int level;

unsigned int Count;
bool if_Pass()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (map[level][i][k] == BOX)
				return false;
		}
	}
	return true;
}
void gamedraw()
{
	for (int i = 0; i < 10; i++)
	{
		for (int k = 0; k < 10;k++)
		{
			switch (map[level][i][k])
			{
			case SPACE:
				cout << "  ";
				break;
			case WALL:
				cout << "※";
				break;
			case DEST:
				cout << "☆";
				break;
			case BOX:
				cout << "口";
				break;
			case PLAYER:
				cout << "Me";
				break;
			case PLAYER+DEST:
				cout << "GG";
				break;
			case BOX+DEST:
				cout << "★";
				break;
			}
			//printf("%d ", map[i][k]);
		}
		cout << endl;
	}
}
void keyevent()	
{
	//首先获取玩家位置
	int i = 0, k = 0;
	for (i = 0; i < 10; i++)
	{
		for (k = 0; k < 10; k++)
		{
			if (map[level][i][k] == PLAYER || map[level][i][k] == PLAYER + DEST)//找到玩家PLAYER,
									//但如果玩家到达目的地 则变成
							//PLAYER + DEST
			{
				goto end;//利用goto跳出二重循环
			}
		}
	}
end:;
	//上下左右119 115 97 100
	//getchar 获取按键消息有弊端，每次输入完还要回车
	char ch = _getch();
	cout << ch << " " << (int)ch;
	switch (tolower(ch))
	{
	case 119:
		//首先要考虑能不能移动
		//若玩家前面空地，直接动，如果是箱子还要判断箱子前面是什么
		if (map[level][i - 1][k] == SPACE || map[level][i - 1][k] == DEST)
		{
			map[level][i - 1][k] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i - 1][k] == BOX && map[level][i - 2][k] != WALL &&map[level][i-2][k] !=BOX)
		{
			map[level][i - 1][k] = map[level][i - 1][k] + PLAYER - BOX;
			map[level][i][k] -= PLAYER;
			map[level][i - 2][k] += BOX;
		}

		break;
	case 115:
		if (map[level][i + 1][k] == SPACE || map[level][i + 1][k] == DEST)
		{
			map[level][i + 1][k] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i + 1][k] == BOX && map[level][i + 2][k] != WALL && map[level][i + 2][k] != BOX)
		{
			map[level][i + 1][k] = map[level][i + 1][k] + PLAYER - BOX;
			map[level][i][k] -= PLAYER;
			map[level][i + 2][k] += BOX;
		}

		break;
	case 97:
		if (map[level][i][k - 1] == SPACE || map[level][i][k - 1] == DEST)
		{
			map[level][i][k - 1] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i][k - 1] == BOX && map[level][i][k - 2] != WALL && map[level][i][k - 2] != BOX)
		{
			map[level][i][k - 1] = map[level][i][k - 1] + PLAYER - BOX;
			map[level][i][k] -= PLAYER;
			map[level][i][k - 2] += BOX;
		}

		break;
	case 100:
		if (map[level][i][k + 1] == SPACE || map[level][i][k + 1] == DEST)
		{
			map[level][i][k + 1] += PLAYER;
			map[level][i][k] -= PLAYER;
		}
		else if (map[level][i][k + 1] == BOX && map[level][i][k + 2] != WALL && map[level][i][k + 2] != BOX)
		{
			map[level][i][k + 1] = map[level][i][k + 1] + PLAYER - BOX;
			map[level][i][k] -= PLAYER;
			map[level][i][k + 2] += BOX;
		}

		break;
	}
}
int main()
{
	//中间不要有空格
	system("mode con lines=15 cols=30");
	while (1)
	{
		system("cls");
		gamedraw();

		if (if_Pass())
		{
			if (++level > 2)
			{
				cout << "You've passed it" << endl;
				break;
			}
		}
		keyevent();
	}
	getchar();//不让程序退出
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
