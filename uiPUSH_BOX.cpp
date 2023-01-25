// 推箱子.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>

#include<cstdlib>
#include <iostream>
#include <conio.h>
#include <graphics.h> 
#include <mmsystem.h>//你干嘛哎哟
#pragma comment(lib,"winmm.lib")
using namespace std;
void Savestate(int r, int c, int dir);
struct Point
{
	int r;//记录行列
	int c;
	int data;
};
struct State
{
	struct Point pos[3];
};
IMAGE img_all[8];

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
void loadimg()
{
	//保存图片
	for (int i = 0; i < 8; i++)
	{

		char file[20] = "";
		sprintf(file,"./ngm/%d.jpg", i);
		loadimage(img_all + i, file, 64, 64);
		//putimage(x, x, img_all + i);//坐标
	}
}
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
unsigned int Back;
enum {Null,Up,Down,Left,Right};
void BkunM1()
{	
	mciSendString("open ./BkunM/1.mp3 alias 你干嘛", 0, 0, 0);
	mciSendString("play 你干嘛 ", 0, 0, 0);
}
void BkunM2()
{
	mciSendString("open ./BkunM/2.mp3 alias 你干嘛哎哟", 0, 0, 0);
	mciSendString("play 你干嘛哎哟 ", 0, 0, 0);
}
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
		for (int k = 0; k < 10; k++)
		{
			int x = 64 * k;
			int y = 64 * i;
			switch (map[level][i][k])
			{
			case SPACE:
				putimage(x, y, img_all + 5);//坐标
				break;
			case WALL:
				putimage(x, y, img_all + 4);//坐标
				break;
			case DEST:
				putimage(x, y, img_all + 2);//坐标
				break;			 
			case BOX:			 
				putimage(x, y, img_all + 6);//坐标
				break;			 
			case PLAYER:		 
				putimage(x, y, img_all + 1);//坐标
				break;			 
			case PLAYER + DEST:	 
				putimage(x, y, img_all + 3);//坐标
				break;			 
			case BOX + DEST:	 
				putimage(x, y, img_all + 7);//坐标
				break;
			}
			//printf("%d ", map[i][k]);
		}
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
	Savestate(i, k, ch);
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
		else if (map[level][i - 1][k] == BOX && map[level][i - 2][k] != WALL && map[level][i - 2][k] != BOX)
		{
			map[level][i - 1][k] = map[level][i - 1][k] + PLAYER - BOX;
			map[level][i][k] -= PLAYER;
			map[level][i - 2][k] += BOX;
		}
		Back = Up;
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
		Back = Down;
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
		Back = Left;
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
		Back = Right;
		break;
	//----------------------------------------------
	}
}
int main()
{
	int mode = 0;
	initgraph(10 * 64, 10 * 64,0);
	loadimg();
	//中间不要有空格
	system("mode con lines=15 cols=30");
	BkunM2();
	while (1)
	{
		system("cls");
		gamedraw();

		if (if_Pass())
		{
			if (++level > 2)
			{
				//outtextxy(250, 250, "Fuck sir");
				break;
			}
		}
		keyevent();
	}
	getchar();//不让程序退出
}
void Savestate(int r,int c,int dir)
{
	State t;
	switch (dir)
	{
	case 119:
		for (int i = 0; i < 3; i++)
		{
			t.pos[i].r = r - i;
			t.pos[i].c = c;
			t.pos[i].data = map[level][t.pos[i].r][t.pos[i].r];
		}
		break;
	case 115:
		for (int i = 0; i < 3; i++)
		{
			t.pos[i].r = r + i;
			t.pos[i].c = c;
			t.pos[i].data = map[level][t.pos[i].r][t.pos[i].r];
		}

		break;
	case 97:
		for (int i = 0; i < 3; i++)
		{
			t.pos[i].r = r;
			t.pos[i].c = c - i;
			t.pos[i].data = map[level][t.pos[i].r][t.pos[i].r];
		}

		break;
	case 100:
		for (int i = 0; i < 3; i++)
		{
			t.pos[i].r = r;
			t.pos[i].c = c + i;
			t.pos[i].data = map[level][t.pos[i].r][t.pos[i].r];
		}
		break;
	}
}