// ������.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>

#include<cstdlib>
#include <iostream>
#include <conio.h>
#include <graphics.h> 
#include <mmsystem.h>//����ﰥӴ
#pragma comment(lib,"winmm.lib")
using namespace std;
void Savestate(int r, int c, int dir);
struct Point
{
	int r;//��¼����
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
//�յ�0 ǽ1 Ŀ�ĵ�2 ����3 ���4 ����Ŀ�ĵ�5 ���Ŀ�ĵ�6
void loadimg()
{
	//����ͼƬ
	for (int i = 0; i < 8; i++)
	{

		char file[20] = "";
		sprintf(file,"./ngm/%d.jpg", i);
		loadimage(img_all + i, file, 64, 64);
		//putimage(x, x, img_all + i);//����
	}
}
enum Mine
{
	SPACE,//�յ�
	WALL,//ǽ
	DEST,//Ŀ�ĵ�
	BOX,//����
	PLAYER
};
//ȷ����ǰ����һ��
int level;

unsigned int Count;
unsigned int Back;
enum {Null,Up,Down,Left,Right};
void BkunM1()
{	
	mciSendString("open ./BkunM/1.mp3 alias �����", 0, 0, 0);
	mciSendString("play ����� ", 0, 0, 0);
}
void BkunM2()
{
	mciSendString("open ./BkunM/2.mp3 alias ����ﰥӴ", 0, 0, 0);
	mciSendString("play ����ﰥӴ ", 0, 0, 0);
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
				putimage(x, y, img_all + 5);//����
				break;
			case WALL:
				putimage(x, y, img_all + 4);//����
				break;
			case DEST:
				putimage(x, y, img_all + 2);//����
				break;			 
			case BOX:			 
				putimage(x, y, img_all + 6);//����
				break;			 
			case PLAYER:		 
				putimage(x, y, img_all + 1);//����
				break;			 
			case PLAYER + DEST:	 
				putimage(x, y, img_all + 3);//����
				break;			 
			case BOX + DEST:	 
				putimage(x, y, img_all + 7);//����
				break;
			}
			//printf("%d ", map[i][k]);
		}
	}
}
void keyevent()
{
	//���Ȼ�ȡ���λ��
	int i = 0, k = 0;
	for (i = 0; i < 10; i++)
	{
		for (k = 0; k < 10; k++)
		{
			if (map[level][i][k] == PLAYER || map[level][i][k] == PLAYER + DEST)//�ҵ����PLAYER,
				//�������ҵ���Ŀ�ĵ� ����
		//PLAYER + DEST
			{
				goto end;//����goto��������ѭ��
			}
		}
	}
end:;
	
	
	//��������119 115 97 100
	//getchar ��ȡ������Ϣ�б׶ˣ�ÿ�������껹Ҫ�س�	
	char ch = _getch();
	Savestate(i, k, ch);
	switch (tolower(ch))
	{
	case 119:
		//����Ҫ�����ܲ����ƶ�
		//�����ǰ��յأ�ֱ�Ӷ�����������ӻ�Ҫ�ж�����ǰ����ʲô
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
	//�м䲻Ҫ�пո�
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
	getchar();//���ó����˳�
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